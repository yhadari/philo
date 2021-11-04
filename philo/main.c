/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:28:11 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/04 20:59:21 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *start_thread(void *value)
{
    t_philo *philo;
    struct timeval current_time;
    
    philo = (t_philo *) value;
	while (1)
	{
        pthread_mutex_lock(&philo->fork[philo->id%philo->args->number]);
        gettimeofday(&current_time, NULL);
        printf("%ld %d has taken a fork\n", current_time.tv_sec*1000, philo->id%philo->args->number);
        pthread_mutex_lock(&philo->fork[philo->id%philo->args->number - 1]);
        gettimeofday(&current_time, NULL);
        printf("%ld %d has taken a fork\n", current_time.tv_sec*1000, philo->id%philo->args->number);
        printf("%ld %d is eating\n", current_time.tv_sec*1000, philo->id%philo->args->number);
        usleep(philo->args->time_to_eat*1000);
        pthread_mutex_unlock(&philo->fork[philo->id%philo->args->number]);
        pthread_mutex_unlock(&philo->fork[philo->id%philo->args->number - 1]);
        gettimeofday(&current_time, NULL);
        printf("%ld %d is sleeping\n", current_time.tv_sec*1000, philo->id%philo->args->number);
        usleep(philo->args->time_to_sleep*1000);
        gettimeofday(&current_time, NULL);
        printf("%ld %d is thinking\n", current_time.tv_sec*1000, philo->id%philo->args->number);
	}
}

void    initialize_args(t_args *args, char **argv)
{
    args->number = ft_atoi(argv[1]);
    args->time_to_die = ft_atoi(argv[2]);
    args->time_to_eat = ft_atoi(argv[3]);
    args->time_to_sleep = ft_atoi(argv[4]);
}

void	creat_thread(t_philo *philos)
{
    int i;

    i = 1;
    while (i <= philos->args->number)
    {
        philos[i - 1].id = i;
        pthread_create(&philos[i - 1].thread, NULL, start_thread, &philos[i - 1]);
        i++;
    }
}

pthread_mutex_t *creat_mutex(int philo_number)
{
    pthread_mutex_t *fork;

    fork = malloc(sizeof(pthread_mutex_t) * philo_number);
    while (philo_number--)
         pthread_mutex_init(&fork[philo_number], NULL);
    return (fork);
}

int	main(int argc, char **argv)
{
    t_args		args;
    t_philo		*philos;
    int			i;
    
    i = 0;
    if (argc != 5 && write(1, "it should be four arguments\n", 28))
        return (0);
    initialize_args(&args, argv);
    philos = malloc(sizeof(t_philo) * args.number);
    philos->args = &args;
    philos->fork = creat_mutex(philos->args->number);
    creat_thread(philos);
    while (i++ < philos->args->number)
        pthread_join(philos[i - 1].thread, NULL);
    return (0);
}