#include "../headers/philosophers.h"

static t_prj   *init_philo(t_prj *prj)
{
    int         i;

    i = -1;
    prj->philos = malloc(sizeof(t_philo) * prj->num_philsr);
    if (!prj->philos)
        clean_prj(&prj, MALF);
    prj->forks = malloc(sizeof(t_philo) * prj->num_philsr);
    if (!prj->forks)
        clean_prj(&prj, MALF);
    while (prj && ++i < prj->num_philsr)
    {
        prj->philos[i] = malloc(sizeof(t_philo));
        if (!prj->philos[i])
            clean_philos(prj, i);
    }
    i = -1;
    while (prj && ++i < prj->num_philsr)
    {
        prj->forks[i] = malloc(sizeof(t_fork));
        if (!prj->forks[i])
            clean_forks(prj, i);
    }
    if (!prj || !prj->philos || !prj->forks)
        clean_prj(&prj, MALF);
    return (prj);
}

t_prj    *init_prj(char **argv, int fd)
{
    t_prj *prj;

    prj = malloc(sizeof(t_prj));
    if (!prj)
    {
        clean_prj(&prj, NULL);
        return (prj);
    }
    prj->stop_game = -1;
    prj->num_philsr = conv_digit(argv[1]);
    prj->t_dead = conv_digit(argv[2]);
    prj->t_eat = conv_digit(argv[3]);
    prj->t_sleep = conv_digit(argv[4]);
    if (prj->num_philsr < MINTIME || prj->t_dead < MINTIME \
        || prj->t_eat < MINTIME || prj->t_sleep < MINTIME)
        clean_prj(&prj, WRINTP);
    prj->philos = NULL;
    prj->forks = NULL;
    return (init_philo(prj));
}
