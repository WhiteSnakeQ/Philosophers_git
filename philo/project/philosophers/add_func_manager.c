/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_func_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/07 12:30:31 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*finish(t_philo *philo)
{
	philo->mother->c_finish++;
	if (philo->mother->c_finish == philo->mother->num_philsr)
		philo->mother->finish = 1;
	return (0);
}

void	change_mutex_eat(t_philo *philo, int mod)
{
	if (mod == LOCK)
	{
		pthread_mutex_lock(&philo->fork[0]->mutex);
		philo->fork[0]->active = 1;
		pthread_mutex_lock(&philo->fork[1]->mutex);
		philo->fork[1]->active = 1;
	}
	else
	{
		pthread_mutex_unlock(&philo->fork[0]->mutex);
		pthread_mutex_unlock(&philo->fork[1]->mutex);
		philo->fork[1]->active = 0;
		philo->fork[0]->active = 0;
	}
}

void	eat_write(t_philo *philo)
{
	action(FORKT, philo, philo->last_act / 1000);
	action(FORKT, philo, philo->last_act / 1000);
	action(EAT, philo, philo->last_act / 1000);
}
