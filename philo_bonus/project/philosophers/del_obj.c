/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/09 11:31:43 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	close_sema(t_prj *prj)
{
	sem_close(prj->write);
	sem_close(prj->sema_forks);
	sem_unlink(SEM_EAT);
	sem_unlink(SEM_WRITE);
	close(prj->fd);
	exit(0);
}
