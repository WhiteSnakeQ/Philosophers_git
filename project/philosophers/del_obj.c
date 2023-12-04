#include "../headers/philosophers.h"

void    clean_philos(t_prj *prj, int size)
{
    int i;

    i = 0;
    if (!prj->philos)
        return ;
    while (i < size)
        free(prj->philos[i++]);
    free(prj->philos);
}

void    clean_forks(t_prj *prj, int size)
{
    int i;

    i = 0;
    if (!prj->forks)
        return ;
    while (i < size)
        free(prj->forks[i++]);
    free(prj->forks);
}

void    clean_prj(t_prj **prj, char *message)
{
    if ((!prj || !*prj) && !message)
    {
        printf("%s", MALF);
        return ;
    }
    if (message)
        write_file((*prj)->fd ,message);
    if ((*prj)->philos)
        clean_philos(*prj, (*prj)->num_philsr);
    if ((*prj)->forks)
        clean_forks(*prj, (*prj)->num_philsr);
    free(*prj);
    *prj = NULL;
    return ;
}
