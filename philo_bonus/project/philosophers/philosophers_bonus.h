/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:59:13 by kreys             #+#    #+#             */
/*   Updated: 2023/12/06 01:35:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H

# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <fcntl.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <sys/stat.h>

# define MALF "Malloc fail\n"
# define FILECRERR "Cannot create file - philo_report\n"
# define WRINTP "Invalid input\n"
# define INVARG "Invalid number of argument\n"

# define FORKT " has taken a fork\n"
# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define DEAD " died\n"
# define THINK " is thinking\n"
# define FINISH_MESS "\nFINISH\n"

# define MINTIME 0
# define MINDTIME 0

# define LOCK 0
# define UNLOCK 1

# define SIZE_TIME 8
# define SIZE_SLEEP 100

typedef struct s_philo
{
	pthread_t		pthread;
	struct s_fork	*fork[2];
	struct s_prj	*mother;
	struct timeval	time;
	int				last_act;
	int				action;
	int				number;
	int				alr_eat;
	int				sleep;
	int				t_dead;
	int				t_l_eat;
}				t_philo;

typedef struct s_prj
{
	int				finish;
	int				close;
	int				c_finish;
	int				num_philsr;
	int				t_dead;
	int				t_eat;
	int				t_sleep;
	int				eat_max;
	int				fd;
	int				milisec;
	int				sec;
	sem_t			*write;
	sem_t			*sema_forks;
	sem_t			*dead;
	struct timeval	time;
	struct s_philo	**philos;
}				t_prj;

//		Main_work
void		start_game(t_prj *prj);
void		made_process(t_prj *prj, int i);
void		*play_one(void *ph);

//		Init_obj
t_prj		*init_prj(char **argv, int fd);

//		Delete_obj
void		clean_prj(t_prj **philo, char *message);
void		clean_philos(t_prj *prj, int size);
void		close_sema(t_prj *prj);

//		Additional_func
char		*to_str(unsigned int digit);
char		*make_time(char *str);
void		write_file(int fd, char *message);
void		action(char *message, t_philo *philo, int time);
void		change_mutex_eat(t_philo *philo, int mod);
void		print_dead(t_philo  *philo);
void		eat_write(t_philo* philo);
void		setup_philo_eat(t_philo **philos, int size, int value);
void 		*finish(t_philo *philo);
int			get_time(t_prj *prj, int mod);
int			log_intit(void);
int			conv_digit(char *str);

#endif