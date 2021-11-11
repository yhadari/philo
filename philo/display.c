/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:04:55 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/11 15:03:19 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display(pthread_mutex_t *print, int id, char *str)
{
	struct timeval	current_time;
	long int		time;

	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(print);
	printf("%ld %d %s\n", time, id, str);
	if (ft_strcmp(str, "died") != 0)
		pthread_mutex_unlock(print);
}
