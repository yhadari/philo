/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:51:34 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/10 17:24:24 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

typedef	struct	s_args
{
    int			number;
    int			time_to_die;
    int			time_to_eat;
    int			time_to_sleep;
    int         number_philo_eat;        
}				t_args;

typedef	struct		s_philo
{
    int				id;
    int             number_eat;
    long int        time_beginning;
    pthread_t		thread;
    pthread_mutex_t	*fork;
    pthread_mutex_t *print;
    t_args			*args;
}					t_philo;

int	ft_atoi(const char *str);
int	ft_strcmp(char *s1, char *s2);

#endif