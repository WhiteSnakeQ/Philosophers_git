/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/07 12:29:51 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	rec_digit(unsigned int *ret, int i, char *str)
{
	int	d;

	d = 0;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	*ret *= 10;
	*ret += str[i] - '0';
	if (str[i + 1])
		d = rec_digit(ret, i + 1, str);
	if (d == -1)
		return (-1);
	return (0);
}

int	conv_digit(char *str)
{
	unsigned int	ret;

	if (!str)
		return (-1);
	ret = 0;
	if (rec_digit(&ret, 0, str) == -1 || ret > __INT_MAX__)
		return (-1);
	return (ret);
}
