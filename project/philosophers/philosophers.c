/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:05:18 by kreys             #+#    #+#             */
/*   Updated: 2023/12/04 11:02:10 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	get_time(t_prj *prj, int mod)
{
	unsigned int	to_str;

	if (mod == 1)
	{
		gettimeofday(&prj->time, NULL);
		prj->sec = prj->time.tv_sec;
		prj->milisec = prj->time.tv_usec;
	}
	else
	{
		gettimeofday(&prj->time, NULL);
		to_str = ((prj->time.tv_sec - prj->sec) * 1000000) + \
			(prj->time.tv_usec - prj->milisec);
		printf("%u\n", to_str / 1000);
		to_str = 0;
	}
}

int	main(int argc, char **argv)
{
	t_prj			*prj;
	int				fd;

	fd = log_intit();
	if (argc <= 4 || argc >= 7)
	{
		write_file(fd, INVARG);
		return (0);
	}
	prj = init_prj(argv, fd);
	if (!prj)
		return (0);
	if (argc == 6)
	{
		prj->stop_game = conv_digit(argv[5]);
		if (prj->stop_game < MINDTIME)
		{
			clean_prj(&prj, WRINTP);
			return (0);
		}
	}
	get_time(prj, 1);
	usleep(prj->num_philsr);
	get_time(prj, 0);
	clean_prj(&prj, NULL);
	return (0);
}
