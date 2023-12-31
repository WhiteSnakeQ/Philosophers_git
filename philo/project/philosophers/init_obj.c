/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/09 10:56:28 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_fork	*init_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (fork);
	fork->active = 0;
	return (fork);
}

static void	setub_philo(t_philo *philo, t_prj *prj, int i)
{
	philo->number = i + 1;
	philo->mother = prj;
	philo->sleep = 0;
	philo->last_act = 0;
	philo->action = 0;
	philo->t_dead = prj->t_dead;
	philo->compl = 0;
	philo->fork[0] = prj->forks[i];
	philo->fork[1] = prj->forks[(i + 1) % prj->num_philsr];
	philo->t_l_eat = 0;
}

static t_prj	*init_philo(t_prj *prj)
{
	int	i;

	i = -1;
	prj->philos = malloc(sizeof(t_philo) * prj->num_philsr);
	if (!prj->philos)
		clean_prj(&prj, MALF);
	prj->forks = malloc(sizeof(t_philo) * prj->num_philsr);
	if (!prj->forks)
		clean_prj(&prj, MALF);
	while (prj && ++i < prj->num_philsr)
	{
		prj->forks[i] = init_fork();
		if (!prj->forks[i])
			clean_forks(prj, i);
	}
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
	{
		clean_prj(&prj, NULL);
		return (prj);
	}
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
	prj->forks = NULL;
	return (init_philo(prj));
}
