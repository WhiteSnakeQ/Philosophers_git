#include "../headers/philosophers.h"

int static str_len(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    write_file(int fd, char *message)
{
    if (fd <= -1)
        return ;
    write(fd, message, str_len(message));
}

int log_intit(void)
{
    int     fd;

    fd = open("philo_report", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        printf("%s", FILECRERR);
    return (fd);
}