/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_func_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/09 10:54:42 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*finish(t_philo **philo)
{
	return (0);
}

int	eat_write(t_philo *philo)
{
	action(FORKT, philo, philo->last_act / 1000);
	action(FORKT, philo, philo->last_act / 1000);
	action(EAT, philo, philo->last_act / 1000);
	return (1);
}

void	kill_all(int size, t_prj *prj)
{
	int	i;

	i = 0;
	while (size > i)
		kill(prj->philos[i++].pid, 15);
	close_sema(prj);
}

void	made_process(t_prj *prj, int i)
{
	int		f;

	while (++i < prj->num_philsr)
		setub_philo(&prj->philos[i], prj, i);
	i = -1;
	get_time(prj, 1);
	while (++i < prj->num_philsr)
	{
		prj->philos[i].pid = fork();
		if (prj->philos[i].pid == -1)
			exit(1);
		if (prj->philos[i].pid == 0)
			play_one(&prj->philos[i]);
	}
	waitpid(-1, &f, 0);
	kill_all(prj->num_philsr, prj);
}
