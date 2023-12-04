#include "../headers/philosophers.h"

void    clean_philo(t_philosophers **philo, char *message)
{
    if (!philo || !*philo)
    {
        printf("%s", MALF);
        return ;
    }
    if (message)
        write_file((*philo)->fd ,message);
    free(*philo);
    *philo = NULL;
    return ;
}
