/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:07:21 by kreys             #+#    #+#             */
/*   Updated: 2023/12/05 15:31:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

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
	if (start == -1 && mod != 1)
		return ;
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

static int	eating(t_philo *philo)
{
	if (philo->fork[0]->active != 0 && philo->fork[1] != 0)
		return (0);
	philo->fork[0]->active = 1;
	philo->fork[1]->active = 1;
	pthread_mutex_lock(&philo->fork[0]->mutex);
	pthread_mutex_lock(&philo->fork[1]->mutex);
	philo->timer = 0;
	action(FORKT, philo, philo->mother, 0);
	action(FORKT, philo, philo->mother, 0);
	philo->sleep = philo->mother->t_eat;
	action(EAT, philo, philo->mother, 0);
	philo->fork[0]->active = 0;
	philo->fork[1]->active = 0;
	pthread_mutex_unlock(&philo->fork[1]->mutex);
	pthread_mutex_unlock(&philo->fork[0]->mutex);
	philo->alr_eat--;
	philo->t_dead = philo->mother->t_dead;
	return (1);
}

static void	sleeping(t_philo *philo)
{
	philo->sleep = philo->mother->t_sleep;
	if (philo->sleep > philo->t_dead)
		philo->sleep = philo->t_dead;
	philo->t_dead -= philo->sleep;
	action(SLEEP, philo, philo->mother, 0);
}

static void	*play_one(void *ph)
{
	static int	alive = -1;
	t_philo		*philo;

	philo = (t_philo *)ph;
	while (alive == -1 && philo->mother->stop_game != 0)
	{
		philo->timer = 1;
		pthread_create(&philo->dead, NULL, &dead_wait, philo);
		while (eating(philo) != 1)
			usleep(1);
		if (philo->alr_eat == 0)
			break ;
		sleeping(philo);
		if (philo->action == -1)
			alive = philo->number;
		if (philo->t_dead <= 0)
			pthread_create(&philo->dead, NULL, &dead_wait, philo);
	}
	philo->mother->c_finish++;
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
	{
		pthread_create(&prj->philos[i]->dead, NULL, &dead_wait, prj->philos[i]);
		pthread_create(&prj->philos[i]->pthread, NULL, &play_one, prj->philos[i]);
	}
	i = -1;
	while (prj->finish == 0)
		usleep(1000);
	i = -1;
	while (++i < prj->num_philsr)
		pthread_mutex_destroy(&prj->forks[i]->mutex);
	usleep(100000);
}