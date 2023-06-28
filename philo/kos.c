/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:36:13 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/22 13:21:09 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
    Function to set every philo as ko. When one philosopher is ko,
    all the others must be ko as well, so the threads can be joined. 
*/

void	ft_set_philos_as_ko(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->philosophers[i].philo_ko_mutex);
		data->philosophers[i].philo_ko = 1;
		if (data->num_of_philos <= 2)
		{
			\
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

int	ft_check_ko(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		gettimeofday(&data->philosophers[i].current_time, NULL);
		pthread_mutex_lock(&data->philosophers[i].last_ate_mutex);
		if (ft_capture_timestamp(data->philosophers[i].current_time, \
					data->philosophers[i].last_ate) >= data->time_to_die)
		{
			printf(COLOR_BLUE "%ld philo %d died" COLOR_RESET "\n", \
					ft_capture_timestamp(data->philosophers[i].current_time, \
						data->philosophers[i].start_time), i + 1);
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

int	ft_is_philo_ko(t_philo *philo)
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
