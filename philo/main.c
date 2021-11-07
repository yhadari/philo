/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:28:11 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/07 19:30:01 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
        gettimeofday(&current_time, NULL);
        printf("%ld %d has taken a fork\n", current_time.tv_sec*1000+current_time.tv_usec/1000, philo->id);
        if (philo->id%2 != 0)
            pthread_mutex_lock(&philo->fork[philo->id%philo->args->number]);
        else
            pthread_mutex_lock(&philo->fork[philo->id - 1]);
        gettimeofday(&current_time, NULL);
        printf("%ld %d has taken a fork\n", current_time.tv_sec*1000+current_time.tv_usec/1000, philo->id);
        philo->time_beginning = current_time.tv_sec*1000+current_time.tv_usec/1000;
        printf("%ld %d is eating\n", current_time.tv_sec*1000+current_time.tv_usec/1000, philo->id);
        //usleep(philo->args->time_to_eat*1000);
        ft_sleep(philo->args->time_to_eat);
        if (philo->id%2 == 0)
            pthread_mutex_unlock(&philo->fork[philo->id%philo->args->number]);
        else
            pthread_mutex_unlock(&philo->fork[philo->id - 1]);
        if (philo->id%2 != 0)
            pthread_mutex_unlock(&philo->fork[philo->id%philo->args->number]);
        else
            pthread_mutex_unlock(&philo->fork[philo->id - 1]);
        gettimeofday(&current_time, NULL);
        printf("%ld %d is sleeping\n", current_time.tv_sec*1000+current_time.tv_usec/1000, philo->id);
        //usleep(philo->args->time_to_sleep*1000);
        ft_sleep(philo->args->time_to_sleep);
        gettimeofday(&current_time, NULL);
        printf("%ld %d is thinking\n", current_time.tv_sec*1000+current_time.tv_usec/1000, philo->id);
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
}

void	creat_thread(t_philo *philos)
{
    struct timeval current_time;
    int i;

    i = 1;
    while (i <= philos->args->number)
    {
        gettimeofday(&current_time, NULL);
        philos[i - 1].id = i;
        philos[i - 1].time_beginning = current_time.tv_sec*1000+current_time.tv_usec/1000;
        pthread_create(&philos[i - 1].thread, NULL, start_thread, &philos[i - 1]);
        i++;
    }
}

void    creat_mutex(t_philo *philos, t_args *args)
{
    int i;

    i = 0;
    philos->fork = malloc(sizeof(pthread_mutex_t) * args->number);
    //philos->print = malloc(sizeof(pthread_mutex_t) * args->number);
    while (i++ < args->number)
    {
        philos[i - 1].args = args;
        philos[i - 1].fork = philos->fork;
        pthread_mutex_init(&philos->fork[i - 1], NULL);
    }
}

int	main(int argc, char **argv)
{
    struct timeval current_time;
    t_args		args;
    t_philo		*philos;
    int			i;
    long int    time;
    
    i = 0;
    if (argc < 5 && write(1, "it should be four/five arguments\n", 33))
        return (0);
    initialize_args(argc, &args, argv);
    philos = malloc(sizeof(t_philo) * args.number);
    creat_mutex(philos, &args);
    creat_thread(philos);
    while (1)
    {
        gettimeofday(&current_time, NULL);
        time = current_time.tv_sec*1000+current_time.tv_usec/1000;
        if ((time - philos[i].time_beginning) > philos->args->time_to_die)
        {
            //pthread_mutex_lock(&print);
            printf("%ld %d died\n", time, philos->id);
            return (0);
        }
        i++;
        i = i%philos->args->number;
    }
    while (i++ < philos->args->number)
        pthread_join(philos[i - 1].thread, NULL);
    return (0);
}