/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:04:43 by kreys             #+#    #+#             */
/*   Updated: 2023/12/05 23:34:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	setub_philo(t_philo *philo, t_prj *prj, int i)
{
	philo->number = i + 1;
	philo->mother = prj;
	philo->sleep = 0;
	philo->action = 0;
	philo->t_dead = prj->t_dead;
	philo->t_l_eat = 0;
}

static t_prj	*init_philo(t_prj *prj)
{
	int	i;

	prj->philos = malloc(sizeof(t_philo) * prj->num_philsr);
	if (!prj->philos)
		clean_prj(&prj, MALF);
	prj->write = malloc(sizeof(t_philo) * prj->num_philsr);
	if (!prj->write)
		clean_prj(&prj, MALF);
	i = -1;
	while (prj && ++i < prj->num_philsr)
	{
		prj->philos[i] = malloc(sizeof(t_philo));
		if (!prj->philos[i])
			clean_philos(prj, i);
		else
			setub_philo(prj->philos[i], prj, i);
	}
	return (prj);
}

void	setup_philo_eat(t_philo **philos, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
		philos[i++]->alr_eat = value;
}

t_prj	*init_prj(char **argv, int fd)
{
	t_prj	*prj;

	prj = malloc(sizeof(t_prj));
	if (!prj)
		return (prj);
	prj->fd = fd;
	prj->eat_max = -1;
	prj->num_philsr = conv_digit(argv[1]);
	prj->t_dead = conv_digit(argv[2]) * 1000;
	prj->t_eat = conv_digit(argv[3]) * 1000;
	prj->t_sleep = conv_digit(argv[4]) * 1000;
	if (prj->num_philsr < MINTIME || prj->t_dead < MINTIME \
		|| prj->t_eat < MINTIME || prj->t_sleep < MINTIME)
	{
		prj->num_philsr = 0;
		clean_prj(&prj, WRINTP);
		return (prj);
	}
	prj->philos = NULL;
	prj->write = NULL;
	sem_unlink("/writing");
	sem_unlink("/dead");
	sem_unlink("/eat");
	prj->write = sem_open("/writing", O_CREAT, S_IRWXU, 1);
	prj->sema_forks = sem_open("/eat", O_CREAT, S_IRWXU, prj->num_philsr);
	prj->dead = sem_open("/dead", O_CREAT, S_IRWXU, 1);
	return (init_philo(prj));
}
