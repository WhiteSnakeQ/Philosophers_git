/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:59:13 by kreys             #+#    #+#             */
/*   Updated: 2023/12/05 15:28:15 by codespace        ###   ########.fr       */
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
# include <string.h>

# define MALF "philo: Malloc fail\n"
# define FILECRERR "philo: Cannot create file - philo_report\n"
# define WRINTP "philo: Invalid input\n"
# define INVARG "philo: Invalid number of argument\n"

# define FORKT " has taken a fork\n"
# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define DEAD " died\n"

# define MINTIME 0
# define MINDTIME 0

# define SIZE_TIME 8
# define SIZE_SLEEP 100

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				active;
}				t_fork;

typedef struct s_philo
{
	pthread_t		pthread;
	pthread_t		dead;
	struct s_fork	*fork[2];
	struct s_prj	*mother;
	int				action;
	int				number;
	int				alr_eat;
	int				sleep;
	int				t_dead;
	int				timer;
}				t_philo;

typedef struct s_prj
{
	int				finish;
	int				c_finish;
	int				num_philsr;
	int				t_dead;
	int				t_eat;
	int				t_sleep;
	int				stop_game;
	int				fd;
	int				milisec;
	int				sec;
	struct timeval	time;
	struct s_philo	**philos;
	struct s_fork	**forks;
}				t_prj;

//		Main_work
void		start_game(t_prj *prj);
void		*dead_wait(void *ph);

//		Init_obj
t_prj		*init_prj(char **argv, int fd);

//		Delete_obj
void		clean_prj(t_prj **philo, char *message);
void		clean_forks(t_prj *prj, int size);
void		clean_philos(t_prj *prj, int size);

//		Additional_func
char		*to_str(unsigned int digit);
void		write_file(int fd, char *message);
int			get_time(t_prj *prj, int mod);
int			log_intit(void);
int			conv_digit(char *str);

#endif