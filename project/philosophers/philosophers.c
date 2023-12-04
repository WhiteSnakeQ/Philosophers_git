#include "../headers/philosophers.h"

int main(int argc, char **argv)
{
    t_philosophers  *philo;
    int              fd;

    fd = log_intit();
    if (argc <= 4 || argc >= 7)
    {
        write_file(fd, INVARG);
        return (0);
    }
    philo = init_philo(argv, fd);
    if (!philo)
        return (0);
    philo->fd = fd;
    if (argc == 6)
    {
        philo->stop_game = conv_digit(argv[5]);
        if (philo->stop_game <= 0)
        {
            clean_philo(&philo,WRINTP);
            return (0);
        }
    }
    printf("%d\n", philo->stop_game);
    printf("%d\n", philo->num_philsr);
    printf("%d\n", philo->t_dead);
    printf("%d\n", philo->t_eat);
    printf("%d\n", philo->t_sleep);
    clean_philo(&philo, NULL);
    return (0);
}