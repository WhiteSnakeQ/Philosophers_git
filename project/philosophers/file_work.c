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

#include "../headers/philosophers.h"

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
