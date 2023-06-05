/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:22:20 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/05 14:24:27 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*

Function to return a timestamp in miliseconds.

*/

long int ft_capture_timestamp(struct timeval current, struct timeval start)
{
    long int timestamp;
    long int seconds;
    long int miliseconds;

    seconds = current.tv_sec - start.tv_sec;
    miliseconds = (current.tv_usec / 1000) - (start.tv_usec / 1000);
    timestamp = seconds * 1000 + miliseconds;
    return (timestamp);
}

/*

Function to get the current time

*/

void ft_right_now(t_philo *philo) 
{
    gettimeofday(&philo->current_time, NULL);
    philo->timestamp_in_ms = ft_capture_timestamp(philo->current_time, philo->start_time);
}


//void ft_usleep_philo(t_philo *philo, long int timeto)
/*void ft_usleep_philo(t_philo *philo)
{
    long int final_time;
    long int now;

    gettimeofday(&philo->generic_data->current_time, NULL); // Get the current time again (ya lo tengo no?)
    now = ft_capture_timestamp(philo->generic_data->current_time, philo->generic_data->start_time);
    final_time = now + timeto;
    while(final_time > now)
    {
        gettimeofday(&philo->generic_data->current_time, NULL); // Get the current time
        now = ft_capture_timestamp(philo->generic_data->current_time, philo->generic_data->start_time);
        //if(philo->generic_data->some_philo_ko == 1)
        //    break;
        usleep(240);
    }
}*/