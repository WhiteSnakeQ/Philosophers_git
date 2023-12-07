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

#include "philosophers_bonus.h"

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

void	close_sema(t_prj *prj)
{
	static int	i = 0;

	if (i++ > 0)
		return ;
	sem_close(prj->write);
	sem_close(prj->sema_forks);
	sem_unlink("/eat");
	sem_unlink("/writing");
}

void	clean_prj(t_prj **prj, char *message)
{
	if ((!prj || !*prj) && !message)
	{
		printf("%s", MALF);
		return ;
	}
	close_sema(*prj);
	if (message)
		write_file((*prj)->fd, message);
	if ((*prj)->philos)
		clean_philos(*prj, (*prj)->num_philsr);
	free(*prj);
	write_file((*prj)->fd, FINISH_MESS);
	if ((*prj)->fd != -1)
		close((*prj)->fd);
	*prj = NULL;
	return ;
}
