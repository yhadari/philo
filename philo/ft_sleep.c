/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:03:52 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/11 15:53:55 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(int time)
{
	struct timeval	current_time;
	long int		first_time;
	long int		time_now;

	gettimeofday(&current_time, NULL);
	first_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		time_now = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		if (time_now - first_time < time)
			usleep(60);
		else
			return ;
	}
}
