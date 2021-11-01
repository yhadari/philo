#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef	struct	s_args
{
    int			number;
    int			time_to_die;
    int			time_to_eat;
    int			time_to_sleep;
}				t_args;

int ft_atoi(const char *str);

#endif