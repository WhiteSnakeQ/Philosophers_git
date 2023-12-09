/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/09 11:43:03 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

	fd = open(NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		printf("%s", FILECRERR);
	return (fd);
}

int	action(char *message, t_philo *philo, int time)
{
	char			*str;
	char			*str2;

	sem_wait(philo->mother->write);
	str = to_str(time);
	str = make_time(str);
	write_file(philo->mother->fd, str);
	write_file(philo->mother->fd, " ");
	str2 = to_str(philo->number);
	write_file(philo->mother->fd, str2);
	write_file(philo->mother->fd, message);
	free(str2);
	free(str);
	sem_post(philo->mother->write);
	return (1);
}

void	print_dead(t_philo *philo)
{
	int			fd;
	int			time;
	char		*str;

	usleep(philo->t_dead);
	sem_wait(philo->mother->write);
	time = get_time(philo->mother, 2);
	fd = philo->mother->fd;
	usleep(1000);
	write_file(fd, "********************\n********************\n");
	str = make_time(to_str(time / 1000));
	write_file(fd, str);
	free(str);
	write_file(fd, " ");
	str = to_str(philo->number);
	write_file(fd, str);
	free(str);
	write_file(fd, DEAD);
	write_file(fd, "********************\n********************\n");
	exit(1);
}
