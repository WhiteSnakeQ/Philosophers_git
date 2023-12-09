/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/09 11:41:23 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating(t_philo *philo)
{
	int	comp;

	if (philo->mother->num_philsr % 2 == 0)
		comp = philo->t_dead - (philo->mother->t_eat - philo->mother->t_sleep);
	else
		comp = philo->t_dead - (philo->mother->t_eat);
	if (comp <= 0 && philo->compl++ != 0)
		print_dead(philo);
	change_mutex_eat(philo, LOCK);
	if (philo->mother->close == 1)
		return ;
	philo->last_act = get_time(philo->mother, 2);
	eat_write(philo);
	if (philo->mother->t_dead <= philo->mother->t_eat)
	{
		philo->last_act = 0;
		philo->t_dead = philo->mother->t_dead;
		print_dead(philo);
	}
	usleep(philo->mother->t_eat);
	philo->t_dead = philo->mother->t_dead - philo->mother->t_eat;
	change_mutex_eat(philo, UNLOCK);
	philo->alr_eat--;
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
		philo->last_act = get_time(philo->mother, 2);
		usleep(philo->t_dead);
		print_dead(philo);
		return ;
	}
	else
	{
		philo->t_dead -= philo->mother->t_sleep;
		usleep(philo->mother->t_sleep);
		philo->last_act = get_time(philo->mother, 2);
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
		pthread_create(&prj->philos[i]->pthread, NULL, \
			&play_one, prj->philos[i]);
	i = -1;
	while (prj->finish == 0)
		usleep(10000);
	usleep(prj->t_dead);
}
