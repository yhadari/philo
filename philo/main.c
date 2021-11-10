/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:28:11 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/10 17:33:30 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>

void    ft_sleep(int time)
{
    struct timeval current_time;
    int first_time;
    int time_now;

    gettimeofday(&current_time, NULL);
    first_time = current_time.tv_sec*1000+current_time.tv_usec/1000;
    while (1)
    {
        gettimeofday(&current_time, NULL);
        time_now = current_time.tv_sec*1000+current_time.tv_usec/1000;
        if (time_now - first_time < time)
            usleep(60);
        else
            return ;
    }
}

void    display(pthread_mutex_t *print, int id, char *str)
{
    struct timeval current_time;
    
    gettimeofday(&current_time, NULL);
    pthread_mutex_lock(print);
    printf("%ld %d %s\n", current_time.tv_sec*1000+current_time.tv_usec/1000, id, str);
    if (ft_strcmp(str, "died") != 0)
        pthread_mutex_unlock(print);
}

void *start_thread(void *value)
{
    t_philo *philo;
    struct timeval current_time;
    
    philo = (t_philo *) value;
	while (1)
	{
        if (philo->id%2 == 0)
            pthread_mutex_lock(&philo->fork[philo->id%philo->args->number]);
        else
            pthread_mutex_lock(&philo->fork[philo->id - 1]);
        display(philo->print, philo->id, "has taken a fork");
        if (philo->id%2 != 0)
            pthread_mutex_lock(&philo->fork[philo->id%philo->args->number]);
        else
            pthread_mutex_lock(&philo->fork[philo->id - 1]);
        display(philo->print, philo->id, "has taken a fork");
        gettimeofday(&current_time, NULL);
        philo->time_beginning = current_time.tv_sec*1000+current_time.tv_usec/1000;
        display(philo->print, philo->id, "is eating");
        philo->number_eat += 1;
        ft_sleep(philo->args->time_to_eat);
        if (philo->id%2 == 0)
            pthread_mutex_unlock(&philo->fork[philo->id%philo->args->number]);
        else
            pthread_mutex_unlock(&philo->fork[philo->id - 1]);
        if (philo->id%2 != 0)
            pthread_mutex_unlock(&philo->fork[philo->id%philo->args->number]);
        else
            pthread_mutex_unlock(&philo->fork[philo->id - 1]);
        display(philo->print, philo->id, "is sleeping");
        ft_sleep(philo->args->time_to_sleep);
        display(philo->print, philo->id, "is thinking");
	}
}

void    initialize_args(int argc, t_args *args, char **argv)
{
    args->number = ft_atoi(argv[1]);
    args->time_to_die = ft_atoi(argv[2]);
    args->time_to_eat = ft_atoi(argv[3]);
    args->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        args->number_philo_eat = ft_atoi(argv[5]);
    else
        args->number_philo_eat = -1;
}

void	 creat_thread(t_philo *philos)
{
    struct timeval current_time;
    int i;

    i = 0;
    while (i < philos->args->number)
    {
        gettimeofday(&current_time, NULL);
        philos[i].id = i + 1;
        philos[i].time_beginning = current_time.tv_sec*1000+current_time.tv_usec/1000;
        pthread_create(&philos[i].thread, NULL, start_thread, &philos[i]);
        i++;
    }
}

void    creat_mutex(int argc, t_philo *philos, t_args *args)
{
    int i;

    i = 0;
    philos->fork = malloc(sizeof(pthread_mutex_t) * args->number);
    philos->print = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(philos->print, NULL);
    while (i < args->number)
    {
        philos[i].args = args;
        philos[i].fork = philos->fork;
        philos[i].print = philos->print;
        if (argc == 6)
            philos[i].number_eat = 0;
        pthread_mutex_init(&philos->fork[i], NULL);
        i++;
    }
}

int number_eat(t_philo  *philos)
{
    int i;

    i = 0;
    if (philos->args->number_philo_eat == -1)
        return (0);
    while (i < philos->args->number)
    {
        if (philos[i].number_eat < philos->args->number_philo_eat)
            return (0);
        i++;
    }
    return (1);
}

int	main(int argc, char **argv)
{
    struct timeval current_time;
    t_args		*args;
    t_philo		*philos;
    int         i;
    long int    time;
    
    i = 0;
    if (argc != 5 && argc != 6)
    {
        write(1, "it should be four/five arguments\n", 33);
        return (0);
    }
    args = malloc(sizeof(t_args));
    initialize_args(argc, args, argv);
    philos = malloc(sizeof(t_philo) * args->number);
    creat_mutex(argc, philos, args);
    creat_thread(philos);
    while (1)
    {
        i = 0;
        while (i < philos->args->number)
        {
            gettimeofday(&current_time, NULL);
            time = current_time.tv_sec*1000+current_time.tv_usec/1000;
            if ((time - philos[i].time_beginning) > philos->args->time_to_die)
            {
                display(philos->print, philos[i].id, "died");
                return (0);
            }
            if (number_eat(philos))
                return (0);
            i++;
        }
    }
    return (0);
}