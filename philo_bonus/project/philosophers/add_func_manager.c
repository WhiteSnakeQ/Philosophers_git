/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   file_work.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: codespace <codespace@student.42.fr>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/12/04 10:04:04 by kreys			 #+#	#+#			 */
/*   Updated: 2023/12/05 12:12:20 by codespace		###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*finish(t_philo *philo)
{
	philo->mother->c_finish++;
	if (philo->mother->c_finish == philo->mother->num_philsr)
		 philo->mother->finish = 1;
	return (0);
}

void	eat_write(t_philo* philo)
{
	action(FORKT, philo, philo->last_act / 1000);
	action(FORKT, philo, philo->last_act / 1000);
	action(EAT, philo, philo->last_act / 1000);
}

void	made_process(t_prj *prj, int i)
{
	pid_t			pid2;

	while (++i < prj->num_philsr)
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			pthread_create(&prj->philos[i]->pthread, NULL, &play_one, prj->philos[i]);
			pthread_join(prj->philos[i]->pthread, NULL);
		}			
	}
	exit(0);
}