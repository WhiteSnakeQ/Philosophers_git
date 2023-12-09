/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:38 by kreys             #+#    #+#             */
/*   Updated: 2023/12/09 11:31:53 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	setub_philo(t_philo *philo, t_prj *prj, int i)
{
	philo->number = i + 1;
	philo->mother = prj;
	philo->t_dead = prj->t_dead;
	philo->t_l_eat = 0;
	philo->complt = 0;
}

static void	init_additional(t_prj *prj)
{
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_EAT);
	prj->write = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
	prj->sema_forks = sem_open(SEM_EAT, O_CREAT, 0644, prj->num_philsr);
}

t_prj	*init_prj(char **argv, int fd, t_prj *prj)
{
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
		exit(0);
	}
	init_additional(prj);
	if (prj->write == SEM_FAILED || \
		prj->sema_forks == SEM_FAILED)
	{
		close_sema(prj);
		exit(0);
	}
	return (prj);
}
