/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:05:18 by kreys             #+#    #+#             */
/*   Updated: 2023/12/04 13:44:16 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

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
	start_game(prj);
	clean_prj(&prj, NULL);
	return (0);
}
