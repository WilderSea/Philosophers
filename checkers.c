/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:17:56 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/08 16:58:44 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Function to capture time left for every philosopher and check if is ko */
/* si el tiempo actual menos el tiempo desde que comio por ultima vez es mayor que el tiempo de vida, ha muerto */
// este checker va a revisar los datos guardados en cada struct de filosofo para comprobar si le queda tiempo de vida

int ft_checker(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_of_philos) 
    {
        pthread_mutex_lock(&data->philosophers[i].write_mutex);
        gettimeofday(&data->philosophers[i].current_time, NULL);
        if (ft_capture_timestamp(data->philosophers[i].current_time, data->philosophers[i].last_ate) >= data->time_to_die)
        {
            printf("%ld philo has died %i\n", ft_capture_timestamp(data->philosophers[i].current_time, data->philosophers[i].start_time), i + 1);
            // bucle para poner a 1 los demas, en cuanto muera uno, matar los demas
            data->philosophers[i].philo_ko = 1;
            pthread_mutex_unlock(&data->philosophers[i].write_mutex);
            return (1);
        }
        else
        {
            pthread_mutex_unlock(&data->philosophers[i].write_mutex);
            i++;
        }
    }
    return (0);
}


int ft_philo_ko(t_philo *philo)
{
    pthread_mutex_lock(&philo->check_mutex);
    if (philo->philo_ko == 1)
    {
        pthread_mutex_unlock(&philo->check_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->check_mutex);
    return (0);
}


