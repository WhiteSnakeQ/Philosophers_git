/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:59:13 by kreys             #+#    #+#             */
/*   Updated: 2023/12/04 13:40:05 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>

# define MALF "philo: Malloc fail\n"
# define FILECRERR "philo: Cannot create file - philo_report\n"
# define WRINTP "philo: Invalid input\n"
# define INVARG "philo: Invalid number of argument\n"

# define MINTIME 1
# define MINDTIME 1

typedef struct s_fork
{
	int				active;
	int				pers;
}				t_fork;

typedef struct s_philo
{
	pthread_t		pthread;
	struct s_fork	*fork[2];
	struct s_prj	*mother;
	int				action;
	int				number;
	int				put_fork;
	int				alr_eat;
	unsigned int	sleep;
}				t_philo;

typedef struct s_prj
{
	int				num_philsr;
	int				t_dead;
	int				t_eat;
	int				t_sleep;
	int				stop_game;
	int				fd;
	int				milisec;
	unsigned int	sec;
	struct timeval	time;
	struct s_philo	**philos;
	struct s_fork	**forks;
}				t_prj;

//		Main_work
void		start_game(t_prj *prj);

//		Init_obj
t_prj		*init_prj(char **argv, int fd);

//		Delete_obj
void		clean_prj(t_prj **philo, char *message);
void		clean_forks(t_prj *prj, int size);
void		clean_philos(t_prj *prj, int size);

//		Additional_func
char		*to_str(unsigned int digit);
void		write_file(int fd, char *message);
void		get_time(t_prj *prj, int mod);
int			log_intit(void);
int			conv_digit(char *str);

#endif