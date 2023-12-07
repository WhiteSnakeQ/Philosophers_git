/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:03:47 by kreys             #+#    #+#             */
/*   Updated: 2023/12/05 13:54:05 by codespace        ###   ########.fr       */
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

void	delete_mut(t_fork **forks, int size)
{
	int i;

	i = 0;
	while (i < size)
		pthread_mutex_destroy(&forks[i++]->mutex);
}
