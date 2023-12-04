/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:07:21 by kreys             #+#    #+#             */
/*   Updated: 2023/12/04 13:41:06 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

static	void	write_status(t_prj *prj, char *message, int numb)
{
	char 		*str;

	write_file(prj->fd, " ");
	str = to_str(numb);
	write_file(prj->fd, str);
	free(str);
	write_file(prj->fd, message);
	write_file(prj->fd, "\n");
}

static int	eating(t_philo *philo)
{
	int		ph;
	int		max;
	int		start;

	start = 0;
	max = philo->mother->num_philsr;
	ph = philo->number;
	if (philo->fork[ph]->active == 0 || philo->fork[ph]->pers == ph)
	{
		philo->fork[ph]->active = 1;
		philo->fork[ph]->pers = ph;
		write_status(philo->mother, " has taken a fork\n", philo->number);
		start++;
	}
	if (philo->fork[(ph + 1) % max]->active == 0 || \
		philo->fork[(ph + 1) % max]->active == ph)
	{
		philo->fork[(ph + 1) % max]->active = 1;
		philo->fork[(ph + 1) % max]->pers = ph;
		start++;
		write_status(philo->mother, " has taken a fork\n", philo->number);
	}
	if (start == 2)
	{
		philo->sleep = philo->mother->t_eat;
		philo->put_fork = 1;
		philo->alr_eat--;
		return (0);
	}
	philo->sleep = 0;
	return (1);
}

static void	action(unsigned int time, char *message, int num, t_prj *prj)
{
	char 		*str;

	write_file(prj->fd, " ");
	str = to_str(num);
	write_file(prj->fd, str);
	free(str);
	write_file(prj->fd, message);
	write_file(prj->fd, "\n");
	usleep(time);
}

static void	*play_one(void *ph)
{
	static int	alive;
	t_philo		*philo;

	philo = (t_philo *)ph;
	alive = -1;
	philo->put_fork = 0;
	philo->sleep = 0;
	philo->alr_eat = philo->mother->stop_game;
	while (alive == -1)
	{
		if (eating(philo) == 0)
			write_status(philo->mother, " is eating\n", philo->number);
		usleep(philo->sleep);
		if (philo->put_fork == 1)
		{
			philo->fork[philo->number]->active = 0;
			philo->fork[(philo->number + 1) % philo->mother->num_philsr]->active = 0;
		}
		action(philo->mother->t_sleep, " is sleeping\n", philo->number, philo->mother);
		usleep(philo->sleep);
		if (philo->alr_eat == -5)
			alive = philo->number;
	}
	if (alive == philo->number)
		write_status(philo->mother, " dead\n", philo->number);
	return (0);
}

void	start_game(t_prj *prj)
{
	int				i;

	i = -1;
	while (++i < prj->num_philsr)
	{
		prj->philos[i]->mother = prj;
		pthread_create(&prj->philos[i]->pthread, NULL, &play_one, prj->philos[i]);
	}
	i = -1;
	usleep(1000000);
}