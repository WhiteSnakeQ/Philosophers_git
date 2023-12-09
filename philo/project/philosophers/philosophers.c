/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/07 12:30:12 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_prj			*prj;
	int				fd;

	fd = log_intit();
	if (fd <= -1)
		return (0);
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
		prj->eat_max = conv_digit(argv[5]);
		if (prj->eat_max < MINDTIME)
			return (clean_prj(&prj, WRINTP));
	}
	setup_philo_eat(prj->philos, prj->num_philsr, prj->eat_max);
	start_game(prj);
	clean_prj(&prj, NULL);
	return (0);
}
