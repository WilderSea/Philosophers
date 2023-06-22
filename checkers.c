/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:17:56 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/22 12:19:57 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
    Function to set every philo as ko. When one philosopher is ko,
    all the others must be ko as well, so the threads can be joined. 
*/

void ft_set_philos_as_ko(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_of_philos)
    {
        pthread_mutex_lock(&data->philosophers[i].philo_ko_mutex);
        data->philosophers[i].philo_ko = 1;
        if (data->num_of_philos <= 2)
        {
            pthread_mutex_unlock(&data->mutexes[data->philosophers[i].fork_right]); 
        }
        pthread_mutex_unlock(&data->philosophers[i].philo_ko_mutex);
        i++;
    }
}
/* 
    Function to check time left for each philosopher and decide if it is KO.
    It checks the values stored in each philo struct. If the difference between "now"
    and the moment the philo "eat last time" is greater than the "time to die", 
    print KO and set all the other philos as KO as well.
*/

int ft_check_ko(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_of_philos) 
    {
        gettimeofday(&data->philosophers[i].current_time, NULL);
        pthread_mutex_lock(&data->philosophers[i].last_ate_mutex);
        if (ft_capture_timestamp(data->philosophers[i].current_time, data->philosophers[i].last_ate) >= data->time_to_die)
        {
            printf(COLOR_BLUE "%ld philo %d died" COLOR_RESET "\n", ft_capture_timestamp(data->philosophers[i].current_time, data->philosophers[i].start_time), i + 1);
            pthread_mutex_unlock(&data->philosophers[i].last_ate_mutex);
            ft_set_philos_as_ko(data);
            return (1);
        }
        else
        {
            pthread_mutex_unlock(&data->philosophers[i].last_ate_mutex);
            i++;
        }
    }
    return (0);
}

/* 
    Function that checks if a philo has been set as ko.
*/

int ft_is_philo_ko(t_philo *philo)
{
    pthread_mutex_lock(&philo->philo_ko_mutex);
    if (philo->philo_ko == 1)
    {
        pthread_mutex_unlock(&philo->philo_ko_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->philo_ko_mutex);
    return (0);
}


/* Add one meal to a philosopher */

void ft_count_meals(t_philo *philo)
{
    pthread_mutex_lock(&philo->meals_mutex);
    philo->meals++;
    pthread_mutex_unlock(&philo->meals_mutex);
}

/*
    Function to check if all philosophers ate at least the required
    number of times. If so, set every philo as "ate everything" and 
    finish simulation.
*/

int ft_check_meals(t_data *data)
{
    int i;
    int count;
    
    i = 0;
    count = 0;
    while(i < data->num_of_philos) 
    {
        pthread_mutex_lock(&data->philosophers[i].meals_mutex);
        if (data->philosophers[i].meals >= data->num_must_eat)
        {
            pthread_mutex_unlock(&data->philosophers[i].meals_mutex);
            pthread_mutex_lock(&data->philosophers[i].finished_mutex);
            data->philosophers[i].finished = 1;
            pthread_mutex_unlock(&data->philosophers[i].finished_mutex);
            pthread_mutex_lock(&data->count_mutex);
            count++;
            pthread_mutex_unlock(&data->count_mutex);
        }
        pthread_mutex_unlock(&data->philosophers[i].meals_mutex);
        i++;
    }
    if (ft_everyphilo_ate(data, count) == 1)
        return (1);
    return (0);
}

int ft_everyphilo_ate(t_data *data, int total)
{
    pthread_mutex_lock(&data->count_mutex);
    if (total == data->num_of_philos)
    {
        pthread_mutex_unlock(&data->count_mutex);
        return (1);
    }
    pthread_mutex_unlock(&data->count_mutex);
    return (0);
}