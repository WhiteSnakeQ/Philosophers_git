/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:03:47 by kreys             #+#    #+#             */
/*   Updated: 2023/12/04 10:03:48 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	clean_philos(t_prj *prj, int size)
{
	int	i;

	i = 0;
	if (!prj->philos)
		return ;
	while (i < size)
		free(prj->philos[i++]);
	free(prj->philos);
}

void	clean_forks(t_prj *prj, int size)
{
	int	i;

	i = 0;
	if (!prj->forks)
		return ;
	while (i < size)
		free(prj->forks[i++]);
	free(prj->forks);
}

void	clean_prj(t_prj **prj, char *message)
{
	if ((!prj || !*prj) && !message)
	{
		printf("%s", MALF);
		return ;
	}
	if (message)
		write_file((*prj)->fd, message);
	if ((*prj)->philos)
		clean_philos(*prj, (*prj)->num_philsr);
	if ((*prj)->forks)
		clean_forks(*prj, (*prj)->num_philsr);
	free(*prj);
	*prj = NULL;
	return ;
}
