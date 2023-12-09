/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:27 by kreys             #+#    #+#             */
/*   Updated: 2023/12/09 12:03:12 by kreys            ###   ########.fr       */
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
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# define MALF "Malloc fail\n"
# define FILECRERR "Cannot create file - philo_report\n"
# define WRINTP "Invalid input\n"
# define INVARG "Invalid number of argument\n"
# define SEMERR "Semafor Error\n"

# define FORKT " has taken a fork\n"
# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define DEAD " died\n"
# define THINK " is thinking\n"

# define NAME "philo_bonus_report.txt"
# define SEM_WRITE "/write"
# define SEM_EAT "/eat"
# define SEM_DEAD "/dead"

# define MINTIME 0
# define MINDTIME 0

# define LOCK 0
# define UNLOCK 1

# define SIZE_TIME 8
# define SIZE_SLEEP 100

typedef struct s_philo
{
	struct s_prj	*mother;
	pid_t			pid;
	int				last_act;
	int				number;
	int				alr_eat;
	int				complt;
	int				t_dead;
	int				t_l_eat;
}				t_philo;

typedef struct s_prj
{
	char			num_philsr;
	int				t_dead;
	int				t_eat;
	int				t_sleep;
	int				eat_max;
	int				fd;
	int				milisec;
	int				sec;
	t_philo			philos[201];
	sem_t			*write;
	sem_t			*sema_forks;
}				t_prj;

//		Main_work
void		start_game(t_prj *prj);
void		made_process(t_prj *prj, int i);
void		*play_one(t_philo *philo);

//		Init_obj
t_prj		*init_prj(char **argv, int fd, t_prj *prj);
void		setub_philo(t_philo *philo, t_prj *prj, int i);

//		Delete_obj
int			clean_prj(t_prj *prj, char *message);
void		close_sema(t_prj *prj);

//		Additional_func
char		*to_str(unsigned int digit);
char		*make_time(char *str);
void		write_file(int fd, char *message);
void		change_mutex_eat(t_philo *philo, int mod);
void		print_dead(t_philo *philo);
void		*finish(t_philo **philo);
int			eat_write(t_philo *philo);
int			action(char *message, t_philo *philo, int time);
int			get_time(t_prj *prj, int mod);
int			log_intit(void);
int			conv_digit(char *str);

#endif