#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>// pthread functions 
#include <sys/time.h> // gettimeofday()  
#include <limits.h>
#include <stdbool.h>

typedef struct s_arg
{
    char **arg;
    unsigned int *data;
    int number;
}t_arg;

unsigned int ft_atoi(char *str);
void   max_atoi(t_arg *info);
void   check_ready_arg(t_arg *info);
void    error(char *arg);


#endif