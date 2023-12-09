/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/09 10:01:15 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include "string.h"

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

char	*make_time(char *str)
{
	char	*to_ret;
	int		size;
	int		m_str;

	m_str = SIZE_TIME;
	to_ret = malloc (sizeof(char) * (m_str + 1));
	if (!to_ret)
		return (str);
	to_ret[m_str--] = '\0';
	memset(to_ret, '0', 7);
	size = 0;
	while (str[size])
		size++;
	while (size >= 0)
		to_ret[m_str--] = str[size--];
	free(str);
	return (to_ret);
}

int	get_time(t_prj *prj, int mod)
{
	unsigned int			digit;
	static struct timeval	time;
	char					*str;

	gettimeofday(&time, NULL);
	if (mod == 1)
	{
		gettimeofday(&time, NULL);
		prj->sec = time.tv_sec;
		prj->milisec = time.tv_usec;
	}
	else if (mod == 2)
	{
		digit = ((time.tv_sec - prj->sec) * 1000000) + \
			(time.tv_usec - prj->milisec);
		return (digit);
	}
	return (0);
}
