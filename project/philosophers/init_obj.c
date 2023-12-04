#include "../headers/philosophers.h"

t_philosophers    *init_philo(char **argv, int fd)
{
    t_philosophers *philo;

    philo = malloc(sizeof(t_philosophers));
    if (!philo)
    {
        clean_philo(&philo, NULL);
        return (philo);
    }
    philo->stop_game = -1;
    philo->num_philsr = conv_digit(argv[1]);
    philo->t_dead = conv_digit(argv[2]);
    philo->t_eat = conv_digit(argv[3]);
    philo->t_sleep = conv_digit(argv[4]);
    if (philo->num_philsr <= 0 || philo->t_dead <= 0 || philo->t_eat <= 0 || philo->t_sleep <= 0)
        clean_philo(&philo, WRINTP);
    return (philo);
}
