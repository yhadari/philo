/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:28:11 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/03 20:42:36 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *start_thread(void *value)
{
    int i;
    t_var *var;
    struct timeval current_time;
    
    var = (t_var *) value;
    i = 0;
	while (1)
	{
        gettimeofday(&current_time, NULL);
        pthread_mutex_lock(&var->fork[i%var->philo.number]);
        printf("%ld %d has taken a fork\n", current_time.tv_sec*1000, i%var->philo.number);
        printf("%ld %d has taken a fork\n", current_time.tv_sec*1000, i%var->philo.number);
        printf("%ld %d is eating\n", current_time.tv_sec*1000, i%var->philo.number);
        usleep(var->philo.time_to_die);
        pthread_mutex_unlock(&var->fork[i%var->philo.number]);
        printf("%ld %d is sleeping\n", current_time.tv_sec*1000, i%var->philo.number);
        usleep(var->philo.time_to_sleep);
        printf("%ld %d is thinking\n", current_time.tv_sec*1000, i%var->philo.number);
	}
}

void    initialize_args(t_args *philo, char **argv)
{
    philo->number = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
}

void	creat_thread(t_var var)
{
    int i;

    i = var.philo.number;
    while (i--)
        pthread_create(&var.thread, NULL, start_thread, &var);
}

pthread_mutex_t *creat_mutex(int philo_number)
{
    pthread_mutex_t *fork;

    fork = malloc(sizeof(pthread_mutex_t) * philo_number);
    while (philo_number--)
         pthread_mutex_init(&fork[philo_number + 1], NULL);
    return (fork);
}

int main(int argc, char **argv)
{
    t_var   var;

    if (argc != 5 && write(1, "it should be four arguments\n", 28))
        return (0);
    initialize_args(&var.philo, argv);
    var.fork = creat_mutex(var.philo.number);
    creat_thread(var);
    pthread_join(var.thread, NULL);

    return (0);
}