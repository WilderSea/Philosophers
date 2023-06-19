/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:55:36 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/19 11:54:43 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
    Every thread will execute this routine. Infinite loop will end only when
    a philo is ko (actions return 1) or when have eaten all their meals.
*/

void *ft_action(void *each_philo)
{
    t_philo *philo;
    
    philo = (t_philo *)each_philo;
    while(ft_finished_meals(philo) != 1)
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
    Function to create threads, one per philosopher. This function as a main 
    thread will continue executing an infinite loop that will run while all 
    philos are alive and until they still have to eat. Important to check 
    about the food along with the ko, to stop simulation after eating enough, 
    avoiding unwanted ko's.
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
    while (ft_checker(data) != 1)
    {
        usleep(500);
        if (data->ate_everything != 0)
        {
            return;
        }
    }
    return ;
}

/* Joining threads. On success, pthread_join returns 0 */
void ft_join_threads(t_data *data)
{
    int i;
    int result;   
    
    i = 0;
    while(i < data->num_of_philos)
    {
        
        printf("JOIN: philo num: %d thread id: %ld\n", data->philosophers[i].philo_num, (unsigned long)data->philosophers[i].tid);
        
        result = pthread_join(data->philosophers[i].tid, NULL);
        if (result != 0)
        {
            ft_putstr_fd("Failed to join the thread.\n", 2);
            exit (1);
        }
        i++;
    }  
    
}
