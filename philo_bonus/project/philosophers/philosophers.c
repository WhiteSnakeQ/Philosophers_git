/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/09 08:28:15 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_prj			prj;
	int				fd;

	fd = log_intit();
	if (fd <= -1)
		return (0);
	if (argc <= 4 || argc >= 7)
	{
		write_file(fd, INVARG);
		return (0);
	}
	prj = *init_prj(argv, fd, &prj);
	if (argc == 6)
	{
		prj.eat_max = conv_digit(argv[5]);
		if (prj.eat_max < MINDTIME)
			exit(0);
	}
	made_process(&prj, -1);
	return (0);
}
