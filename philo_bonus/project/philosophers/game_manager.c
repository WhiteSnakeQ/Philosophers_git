/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/09 10:31:35 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	eating(t_philo *philo)
{
	int	comp;

	if (philo->mother->num_philsr % 2 == 0)
		comp = philo->t_dead - (philo->mother->t_eat - philo->mother->t_sleep);
	else
		comp = philo->t_dead - (philo->mother->t_eat);
	if (comp <= 0 && philo->complt != 0)
		print_dead(philo);
	sem_wait(philo->mother->sema_forks);
	sem_wait(philo->mother->sema_forks);
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
	sem_post(philo->mother->sema_forks);
	sem_post(philo->mother->sema_forks);
	philo->alr_eat--;
	philo->complt++;
}

static int	sleep_p(t_philo *philo)
{
	int	time;

	time = get_time(philo->mother, 2);
	action(SLEEP, philo, time / 1000);
	if (philo->t_dead - philo->mother->t_sleep <= 0)
	{
		philo->last_act = get_time(philo->mother, 2);
		usleep(philo->t_dead);
		print_dead(philo);
		return (666);
	}
	else
	{
		philo->t_dead -= philo->mother->t_sleep;
		usleep(philo->mother->t_sleep);
		philo->last_act = get_time(philo->mother, 2);
		time = get_time(philo->mother, 2);
		action(THINK, philo, time / 1000);
	}
	return (0);
}

void	*play_one(t_philo *philo)
{
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
			return (finish(&philo));
		if (sleep_p(philo) == 666)
			return (0);
	}
	return (finish(&philo));
}
