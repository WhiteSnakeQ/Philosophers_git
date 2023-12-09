/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/07 12:30:24 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_philos(t_prj *prj, int size)
{
	int	i;

	i = 0;
	if (!prj->philos || size <= 0)
		return ;
	while (i < size)
	{
		free(prj->philos[i]);
		prj->philos[i++] = NULL;
	}
	free(prj->philos);
}

void	clean_forks(t_prj *prj, int size)
{
	int	i;

	i = 0;
	if (!prj->forks || size <= 0)
		return ;
	while (i < size)
		free(prj->forks[i++]);
	free(prj->forks);
}

int	clean_prj(t_prj **prj, char *message)
{
	if ((!prj || !*prj) && !message)
	{
		printf("%s", MALF);
		return (0);
	}
	if (message)
		write_file((*prj)->fd, message);
	if ((*prj)->philos)
		clean_philos(*prj, (*prj)->num_philsr);
	if ((*prj)->forks)
		clean_forks(*prj, (*prj)->num_philsr);
	free(*prj);
	*prj = NULL;
	return (0);
}

void	delete_mut(t_fork **forks, int size)
{
	int	i;

	i = 0;
	while (i < size)
		pthread_mutex_destroy(&forks[i++]->mutex);
}
