#ifndef PHILOSOPHERS_H

# define PHILOSOFERS_H

# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "fcntl.h"

# define MALF "philo: Malloc fail\n"
# define FILECRERR "philo: Cannot create file - philo_report\n"
# define WRINTP "philo: Invalid input\n"
# define INVARG "philo: Invalid number of argument\n"

typedef struct s_philosophers
{
    int             num_philsr;
    int             t_dead;
    int             t_eat;
    int             t_sleep;
    int             stop_game;
    int             fd;
}               t_philosophers;

//              Init_obj
t_philosophers  *init_philo(char **argv, int fd);

//              Delete_obj
void            clean_philo(t_philosophers **philo, char *message);

//              Additional_func
void            write_file(int fd, char *message);
int             log_intit(void);
int             conv_digit(char *str);

#endif