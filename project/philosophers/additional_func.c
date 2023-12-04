/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:02:39 by kreys             #+#    #+#             */
/*   Updated: 2023/12/04 13:43:59 by kreys            ###   ########.fr       */
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
	return (str);
}
