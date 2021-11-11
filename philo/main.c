/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:28:11 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/11 15:00:10 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_args(int argc, t_args *args, char **argv)
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

void	creat_thread(t_philo *philos)
{
	struct timeval	current_time;
	int				i;
	int				time;

	i = 0;
	while (i < philos->args->number)
	{
		time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		gettimeofday(&current_time, NULL);
		philos[i].id = i + 1;
		philos[i].time_beginning = time;
		pthread_create(&philos[i].thread, NULL, start_thread, &philos[i]);
		i++;
	}
}

void	creat_mutex(int argc, t_philo *philos, t_args *args)
{
	int	i;

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

int	number_eat(t_philo *philos)
{
	int	i;

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
	t_args		*args;
	t_philo		*philos;
	int			i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		write(1, "it should be four/five arguments\n", 33);
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 0)
	{
		write(1, "the number must be >= 0\n", 24);
		return (0);
	}
	args = malloc(sizeof(t_args));
	initialize_args(argc, args, argv);
	philos = malloc(sizeof(t_philo) * args->number);
	creat_mutex(argc, philos, args);
	creat_thread(philos);
	return (checker(philos));
}
