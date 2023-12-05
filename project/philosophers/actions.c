/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   actions.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: codespace <codespace@student.42.fr>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/12/05 12:18:52 by codespace		 #+#	#+#			 */
/*   Updated: 2023/12/05 13:40:22 by codespace		###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../headers/philosophers.h"

static void print_dead(t_philo  *philo)
{
	int	 		fd;
	char		*str;
	static int i = 0;

	if (i != 0)
		return ;
	i++;
	fd = philo->mother->fd;
	write_file(fd, "\n\n\n********************");
	write_file(fd, "\n********************\n");
	get_time(philo->mother, 0);
	write_file(fd, " ");
	str = to_str(philo->number);
	write_file(fd, str);
	free(str);
	write_file(fd, DEAD);
	write_file(fd, "********************");
	write_file(fd, "\n********************\n");
}

void	*dead_wait(void *ph)
{	
	t_philo			*philo;
	static int		finish = 0;

	philo = (t_philo *)ph;
	if (philo->timer == 0)
		return (0);
	if (philo->t_dead == 0)
	{
		print_dead(philo);
		finish = 1;
		philo->mother->finish = 1;
		philo->action = -1;
	}
	usleep(philo->t_dead);
	if (finish == 1 || philo->timer == 0)
		return (0);
	print_dead(philo);
	finish = 1;
	philo->mother->finish = 1;
	philo->action = -1;
	return (0);
}
