/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:04:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/05 12:12:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	write_file(int fd, char *message)
{
	if (fd <= -1)
		return ;
	write(fd, message, str_len(message));
}

int	log_intit(void)
{
	int	fd;

	fd = open("philo_report.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		printf("%s", FILECRERR);
	return (fd);
}

void	action(char *message, t_philo *philo, int time)
{
	char 		*str;
	char		*str2;

	pthread_mutex_lock(&philo->mother->mutex_eat);
	if (philo->mother->close == 1)
		return ;
	str = to_str(time);
	str = make_time(str);
	write_file(philo->mother->fd, str);
	write_file(philo->mother->fd, " ");
	str2 = to_str(philo->number);
	write_file(philo->mother->fd, str2);
	free(str2);
	write_file(philo->mother->fd, message);
	free(str);
	pthread_mutex_unlock(&philo->mother->mutex_eat);
}

void	print_dead(t_philo  *philo)
{
	int	 		fd;
	int			time;
	char		*str;

	pthread_mutex_lock(&philo->mother->dead);
	time = get_time(philo->mother, 2);
	philo->mother->close = 1; 
	delete_mut(philo->mother->forks, philo->mother->num_philsr);
	pthread_mutex_destroy(&philo->mother->mutex_eat);
	fd = philo->mother->fd;
	philo->mother->finish = 1;
	usleep(1000);
	write_file(fd, "\n********************");
	write_file(fd, "\n********************\n");
	str = make_time(to_str(time / 1000));
	write_file(fd, str);
	free(str);
	write_file(fd, " ");
	str = to_str(philo->number);
	write_file(fd, str);
	free(str);
	write_file(fd, DEAD);
	write_file(fd, "********************");
	write_file(fd, "\n********************\n");
	pthread_mutex_destroy(&philo->mother->dead);
}
