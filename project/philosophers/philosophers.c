#include "../headers/philosophers.h"

int main(int argc, char **argv)
{
    t_prj  *prj;
    int              fd;

    fd = log_intit();
    if (argc <= 4 || argc >= 7)
    {
        write_file(fd, INVARG);
        return (0);
    }
    prj = init_prj(argv, fd);
    if (!prj)
        return (0);
    prj->fd = fd;
    if (argc == 6)
    {
        prj->stop_game = conv_digit(argv[5]);
        if (prj->stop_game < MINDTIME)
        {
            clean_prj(&prj, WRINTP);
            return (0);
        }
    }
    clean_prj(&prj, NULL);
    start_game(prj);
    return (0);
}