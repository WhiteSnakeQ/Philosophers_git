/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:02:39 by kreys             #+#    #+#             */
/*   Updated: 2023/12/04 13:29:44 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

static int	calc_size(unsigned int digit)
{
	int	i;

	i = 1;
	while (digit > 9)
	{
		digit /= 10;
		i++;
	}
	return (i);
}

static void	fill_str(char *str, int i, int digit)
{
	if (digit > 9)
	{
		fill_str(str, i - 1, digit / 10);
		str[i] = (digit % 10) + '0';
	}
	else
		str[i] = digit + '0';
}

char	*to_str(unsigned int digit)
{
	int		size;
	char	*str;

	size = calc_size(digit);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (str);
	str[size] = '\0';
	if (digit > 9)
		fill_str(str, size - 1, digit);
	else
		str[0] = digit + '0';
	return (str);
}

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
