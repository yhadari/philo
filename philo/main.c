/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:28:11 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/05 20:48:43 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_sleep(int time)
{
    int i;

    i = 0;
    while (i < time)
    {
        i += 60;
        if ((time - i) < 60)
            usleep(time - i);
        else
            usleep(60);
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
        ft_sleep(philo->args->time_to_eat*1000);
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
        ft_sleep(philo->args->time_to_sleep*1000);
        gettimeofday(&current_time, NULL);
        printf("%ld %d is thinking\n", current_time.tv_sec*1000+current_time.tv_usec/1000, philo->id);
        philo->time_end = current_time.tv_sec*1000+current_time.tv_usec/1000;
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

pthread_mutex_t *creat_mutex(t_philo *philos, t_args *args)
{
    int i;
    pthread_mutex_t *fork;

    i = 0;
    fork = malloc(sizeof(pthread_mutex_t) * args->number);
    while (i++ < args->number)
    {
        philos[i - 1].args = args;
        philos[i - 1].fork = fork;
        pthread_mutex_init(&fork[i - 1], NULL);
    }
    return (fork);
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
    philos->fork = creat_mutex(philos, &args);
    creat_thread(philos);
    while (1)
    {
        gettimeofday(&current_time, NULL);
        time = current_time.tv_sec*1000+current_time.tv_usec/1000;
        if ((time - philos[i].time_beginning) > philos->args->time_to_die)
        {
            printf("%ld %d died\n", time, philos->id);
            return (0);
        }
        i++;
        i = i%philos->args->number;
    }
    //while (i++ < philos->args->number)
    //    pthread_join(philos[i - 1].thread, NULL);
    /*i = 0;
    while (i++ < philos->args->number)
        pthread_mutex_destroy(philos[i - 1].fork);*/
    return (0);
}