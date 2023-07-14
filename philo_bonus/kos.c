/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:36:13 by msintas-          #+#    #+#             */
/*   Updated: 2023/07/13 18:51:08 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
    Function to set every philo as ko. When one philosopher is ko,
    all the others must be ko as well, 
	
	¿so the threads can be joined. ??
*/

void	ft_set_philos_as_ko(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philosophers[i].philo_ko = 1;
		if (data->num_of_philos <= 2)
		{
			sem_post(data->forks_sem);
		}
		i++;
	}
}

/*
Function to check time left for each philosopher and decide if it is KO.
It checks the values stored in each philo struct. If the difference between "now"
and the moment the philo "eat last time" is greater than the "time to die", 
print KO and set all the other philos as KO as well.
*/

int	ft_check_ko(t_philo *supervised_philo)
{
		gettimeofday(&supervised_philo->current_time, NULL);
		if (ft_capture_timestamp(supervised_philo->current_time, \
					supervised_philo->last_ate) >= supervised_philo->generic_data->time_to_die)
		{
			printf(COLOR_BLUE "%ld philo %d died" COLOR_RESET "\n", \
					ft_capture_timestamp(supervised_philo->current_time, \
						supervised_philo->start_time), supervised_philo->philo_num);
			//ft_set_philos_as_ko(data);
			return (1);
		}
	return (0);
}

/* 
    Function that checks if a philo has been set as ko.
*/

int	ft_is_philo_ko(t_philo *philo)
{
	if (philo->philo_ko == 1)
	{
		return (1);
	}
	return (0);
}
