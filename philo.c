/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:55:36 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/16 16:30:01 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void *ft_action(void *each_philo)
{
    t_philo *philo;
    
    philo = (t_philo *)each_philo;
    while(philo->meals != 0)
    {
        if (ft_philo_eats(philo) == 1)
        {
            return (NULL);
        }
        if (ft_philo_sleeps(philo) == 1) 
        {
            return (NULL);
        }
        ft_philo_thinks(philo);   
    }
    printf("Philosofo/Thread num: %d is exiting...\n", philo->philo_num);
    return (NULL);
}

/* 
Function to create threads, one per philosopher.
Main thread continues executing the code that follows the pthread_create 
call without waiting for the newly created threads to finish its execution.
*/

void ft_create_philos(t_data *data)
{
    int i;
    int result; 

    i = 0;
    while(i < data->num_of_philos)
    {
        if (data->philosophers[i].philo_num % 2 != 0)
            usleep(40);
        gettimeofday(&data->philosophers[i].start_time, NULL);
        data->philosophers[i].last_ate = data->philosophers[i].start_time;
        result = pthread_create(&data->philosophers[i].tid, NULL, &ft_action, &data->philosophers[i]);
        if (result != 0)
        {
            ft_putstr_fd("Failed to create thread.\n", 2);
            exit (1);
        }
        i++;   
    }
    while(1)
    {
        usleep(500);
        if (ft_checker(data) == 1)
            return ;
    }
    return ;
}

void ft_join_threads(t_data *data)
{
    int i;
    int result;   
    
    i = 0;
    while(i < data->num_of_philos)
    {
        
        printf("JOIN: philo num: %d thread id: %ld\n", data->philosophers[i].philo_num, (unsigned long)data->philosophers[i].tid);
        
        result = pthread_join(data->philosophers[i].tid, NULL);
        if (result != 0) // on success, pthread_join returns 0
        {
            ft_putstr_fd("Failed to join the thread.\n", 2);
            exit (1);
        }
        i++;
    }  
    
}
