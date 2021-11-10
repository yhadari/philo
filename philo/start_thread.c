/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:29:27 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/10 22:54:09 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    check_fork(t_philo *philo, char *str)
{
    if (ft_strcmp("lock", str) == 0)
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
    }
    else
    {
        if (philo->id%2 == 0)
            pthread_mutex_unlock(&philo->fork[philo->id%philo->args->number]);
        else
            pthread_mutex_unlock(&philo->fork[philo->id - 1]);
        if (philo->id%2 != 0)
            pthread_mutex_unlock(&philo->fork[philo->id%philo->args->number]);
        else
            pthread_mutex_unlock(&philo->fork[philo->id - 1]);
    }
}

void *start_thread(void *value)
{
    t_philo *philo;
    struct timeval current_time;
    
    philo = (t_philo *) value;
	while (1)
	{
        check_fork(philo, "lock");
        gettimeofday(&current_time, NULL);
        philo->time_beginning = current_time.tv_sec*1000+current_time.tv_usec/1000;
        display(philo->print, philo->id, "is eating");
        philo->number_eat += 1;
        ft_sleep(philo->args->time_to_eat);
        check_fork(philo, "unlock");
        display(philo->print, philo->id, "is sleeping");
        ft_sleep(philo->args->time_to_sleep);
        display(philo->print, philo->id, "is thinking");
	}
}