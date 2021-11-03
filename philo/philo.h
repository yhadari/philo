#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

typedef	struct	s_args
{
    int			number;
    int			time_to_die;
    int			time_to_eat;
    int			time_to_sleep;
}				t_args;

typedef struct s_var
{
    pthread_t       thread;
    pthread_mutex_t *fork;
    t_args          philo;
}               t_var;

int ft_atoi(const char *str);

#endif