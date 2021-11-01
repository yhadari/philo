/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadari <yhadari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:28:11 by yhadari           #+#    #+#             */
/*   Updated: 2021/11/01 20:33:49 by yhadari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char    *hello;
int     var = 0;
//p_tread_mutex_t hello_mutex;

void *print_thread(void *value)
{
    //pthread_mutex_lock(&hello_mutex);
    if (var == 0)
    {
        hello = "yassine";
        var = 1;
    }
    //pthread_mutex_unlock(&hello_mutex);
    value = NULL;
    return (NULL);
}

void *print_thread2(void *value)
{
    size_t i = -1;
    if (var == 1)
    {
        while (++i < strlen(hello))
            printf("%c\n", hello[i]);
        var = 0;
    }
    value = NULL;
    return (NULL);
}

void    initialize_args(t_args *philo, char **argv)
{
    philo->number = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
}

int main(int argc, char **argv)
{
    pthread_t   thread;
    t_args      philo;

    if (argc != 5 && write(1, "it should be four arguments\n", 28))
        return (0);
    initialize_args(&philo, argv);
    pthread_create(&thread, NULL, print_thread, NULL);
    pthread_create(&thread, NULL, print_thread2, NULL);
    pthread_join(thread, NULL);

    return (0);
}