#include "../headers/philosophers.h"

static int rec_digit(int *ret, int i, char *str)
{
    int d;

    if (d == -1)
        return (-1);
    if (str[i] < '0' || str[i] > '9')
        return (-1);
    *ret *= 10;
    *ret += str[i] - '0';
    if(str[i + 1])
        d = rec_digit(ret, i + 1, str);
}

int conv_digit(char *str)
{
    unsigned int    ret;
    int             i;

    if (!str)
        return (-1);
    ret = 0;
    if (rec_digit(&ret, 0, str) == -1 || ret > __INT_MAX__)
        return (-1);
    return (ret);    
}