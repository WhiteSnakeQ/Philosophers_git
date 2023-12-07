/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:07:21 by kreys             #+#    #+#             */
/*   Updated: 2023/12/06 01:36:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eating(t_philo *philo)
{
	static int	last_eat = 0;
	static int	finish = 0;

	if (last_eat + philo->mother->t_eat >= philo->t_l_eat + philo->t_dead && (philo->fork[0]->active == 1 || philo->fork[1]->active == 1))
	{
		usleep(philo->t_dead);
		print_dead(philo);
		return (0);
	}
	change_mutex_eat(philo, LOCK);
	if (philo->mother->close == 1)
		return (0);
	philo->last_act = get_time(philo->mother, 2);
	eat_write(philo);
	usleep(philo->mother->t_sleep);
	philo->t_l_eat = get_time(philo->mother, 2);
	philo->t_dead = philo->mother->t_dead;
	if (++finish % (philo->mother->num_philsr / 2) == 0)
		last_eat += philo->mother->t_eat;
	change_mutex_eat(philo, UNLOCK);
	philo->alr_eat--;
	return (1);
}

static void	sleep_p(t_philo *philo)
{
	int	time;

	if (philo->mother->close == 1)
		return ;
	time = get_time(philo->mother, 2);
	action(SLEEP, philo, time / 1000);
	if (philo->t_dead - philo->mother->t_sleep <= 0)
	{
		usleep(philo->t_dead);
		print_dead(philo);
		return ;
	}
	else
	{
		philo->t_dead -= philo->mother->t_sleep;
		usleep(philo->mother->t_sleep);
		time = get_time(philo->mother, 2);
		action(THINK, philo, time / 1000);
	}
}

static void	*play_one(void *ph)
{
	t_philo		*philo;

	philo = (t_philo *)ph;
	if (philo->mother->num_philsr == 1)
	{
		usleep(philo->t_dead);
		print_dead(philo);
		return (0);
	}
	while (philo->mother->eat_max != 0)
	{
		eating(philo);
		if (philo->alr_eat == 0)
			return (finish(philo));
		sleep_p(philo);
		if (philo->mother->close == 1)	
			return (finish(philo));
	}
	return (0);
}

void	start_game(t_prj *prj)
{
	int				i;

	i = -1;
	prj->finish = 0;
	prj->c_finish = 0;
	prj->close = 0;
	while (++i < prj->num_philsr)
		pthread_mutex_init(&prj->forks[i]->mutex, NULL);
	pthread_mutex_init(&prj->mutex_eat, NULL);
	pthread_mutex_init(&prj->dead, NULL);
	i = -1;
	get_time(prj, 1);
	while (++i < prj->num_philsr)
		pthread_create(&prj->philos[i]->pthread, NULL, &play_one, prj->philos[i]);
	i = -1;
	while (prj->finish == 0)
		usleep(10000);
	usleep(prj->t_eat + prj->t_sleep);
}