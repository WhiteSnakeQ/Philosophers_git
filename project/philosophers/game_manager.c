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

#include "../headers/philosophers.h"
#include "pthread.h"

static void	action(char *message, t_philo *philo, t_prj *prj, int mod)
{
	char 					*str;
	static pthread_mutex_t	mutex;
	static int				start = 10;

	if (start == 10)
	{
		start++;
		pthread_mutex_init(&mutex, NULL);
	}
	if (mod == 666)
	{
		pthread_mutex_destroy(&mutex);
		start = -5;
	}
	if (start == -5)
		return ;
	pthread_mutex_lock(&mutex);
	if (philo->action == -1)
		return ;
	get_time(prj, 0);
	write_file(prj->fd, " ");
	str = to_str(philo->number);
	write_file(prj->fd, str);
	free(str);
	write_file(prj->fd, message);
	pthread_mutex_unlock(&mutex);
	usleep(philo->sleep);
	philo->sleep = 0;
	if (mod == 1)
	{
		pthread_mutex_destroy(&mutex);
		start = -5;
	}
}

void	delete_mut(t_fork **forks, int size)
{
	int i;

	i = 0;
	while (i < size)
		pthread_mutex_destroy(&forks[i++]->mutex);
}

void	print_dead(t_philo  *philo)
{
	int	 		fd;
	char		*str;
	static int i = 0;

	if (i != 0)
		return ;
	i++;
	delete_mut(philo->mother->forks, philo->mother->num_philsr);
	fd = philo->mother->fd;
	philo->mother->finish = 1;
	action(NULL, NULL, NULL, 666);
	write_file(fd, "\n********************");
	write_file(fd, "\n********************\n");
	get_time(philo->mother, 0);
	write_file(fd, " ");
	str = to_str(philo->number);
	write_file(fd, str);
	free(str);
	write_file(fd, DEAD);
	write_file(fd, "********************");
	write_file(fd, "\n********************\n");
}

static int	eating(t_philo *philo)
{
	static int	last_eat = 0;

	if (!philo)
		return (0);
	if (last_eat + philo->mother->t_eat > philo->t_l_eat + philo->t_dead && (philo->fork[0]->active == 1 || philo->fork[1]->active == 1))
	{
		usleep(philo->t_dead);
		print_dead(philo);
		return (0);
	}
	pthread_mutex_lock(&philo->fork[0]->mutex);
	philo->fork[0]->active = 1;
	pthread_mutex_lock(&philo->fork[1]->mutex);
	philo->fork[1]->active = 1;
	last_eat = get_time(philo->mother, 2);
	action(FORKT, philo, philo->mother, 0);
	action(FORKT, philo, philo->mother, 0);
	philo->sleep = philo->mother->t_eat;
	action(EAT, philo, philo->mother, 0);
	philo->t_l_eat = get_time(philo->mother, 2);
	philo->t_dead = philo->mother->t_dead;
	pthread_mutex_unlock(&philo->fork[0]->mutex);
	pthread_mutex_unlock(&philo->fork[1]->mutex);
	if (!philo)
		return (0);
	philo->fork[1]->active = 0;
	philo->fork[0]->active = 0;
	philo->alr_eat--;
	return (1);
}

static void	sleeping(t_philo *philo)
{
	philo->sleep = philo->mother->t_sleep;
	if (philo->sleep >= philo->t_dead)
		philo->sleep = philo->t_dead;
	philo->t_dead -= philo->sleep;
	action(SLEEP, philo, philo->mother, 0);
}

static void	*play_one(void *ph)
{
	static int	alive = -1;
	t_philo		*philo;

	philo = (t_philo *)ph;
	philo->t_l_eat = 0;
	usleep(100);
	if (philo->mother->num_philsr == 1)
	{
		usleep(philo->t_dead);
		print_dead(philo);
		return (0);
	}
	while (alive == -1 && philo->mother->eat_max != 0)
	{
		if (eating(philo) == 0)
			return (0);
		sleeping(philo);
		if (philo->action == -1)
			alive = philo->number;
		action(THINK, philo, philo->mother, 0);
	}
	philo->mother->c_finish++;
	if (philo->action == philo->number)
		print_dead(philo);
	if (philo->mother->c_finish == philo->mother->num_philsr)
		philo->mother->finish = 1;
	return (0);
}

void	start_game(t_prj *prj)
{
	int				i;

	i = -1;
	prj->finish = 0;
	prj->c_finish = 0;
	while (++i < prj->num_philsr)
		pthread_mutex_init(&prj->forks[i]->mutex, NULL);
	i = -1;
	get_time(prj, 1);
	while (++i < prj->num_philsr)
		pthread_create(&prj->philos[i]->pthread, NULL, &play_one, prj->philos[i]);
	i = -1;
	while (prj->finish == 0)
		usleep(1000);
	i = -1;
	while (++i < prj->num_philsr)
		pthread_mutex_destroy(&prj->forks[i]->mutex);
	usleep(prj->t_eat +prj->t_sleep);
}