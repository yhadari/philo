/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:11:50 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/11 15:02:17 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checker(t_philo *philos)
{
	struct timeval	current_time;
	long int		time;
	int				i;

	while (1)
	{
		i = 0;
		while (i < philos->args->number)
		{
			gettimeofday(&current_time, NULL);
			time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
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
}
