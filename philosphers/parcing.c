#include  "philo.h"

void    error(char *arg)
{
    printf("Error : %s\n", arg);
    exit(1);
}

unsigned int ft_atoi(char *str)
{
    unsigned int number;

    number = 0;
    if (number > INT_MAX)
        return((unsigned int)INT_MAX + 87326);
    while (*str)
    {
        number = (int)*str - (int)'0' + number;
        str++;
        if (*str != '\0')
            number = number * 10;
    }
    return (number);
}

void   max_atoi(t_arg *info)
{
    int i;
    int j;

    i = 1;
    j = 0;
    info->data = (unsigned int *)malloc(sizeof(int) * info->number);
    if (!info->data)
        error("allocation failed");
    while(i < info->number)
    {
        info->data[j] = ft_atoi(info->arg[i]);
        if (info->data[j] > INT_MAX)
        {
            free(info->data);
            error("excceding INT_MAX");
        }
        i++;
        j++;
    }
}

void   check_ready_arg(t_arg *info)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (i < info->number)
    {
        j = 0;
        while (info->arg[i][j] != 0)
        {
            if ((info->arg[i][j] < '0' || info->arg[i][j] > '9') && info->arg[i][j] != '\0')
            {
                if(info->arg[i][0] == '-')
                    error("Only positive Number");
                error("Only Numbers");
            }
            j++;
        }
        i++;
    }
    max_atoi(info);
}