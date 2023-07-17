/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:36:13 by msintas-          #+#    #+#             */
/*   Updated: 2023/07/17 10:32:38 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
    Function to set the supervised philo as ko.
	Release forks before leaving when the number of philosophers is 2 or less.
*/

void	ft_set_supervised_philo_as_ko(t_philo *supervised_philo)
{
	//sem_wait(supervised_philo->generic_data->check_sem);
	supervised_philo->philo_ko = 1;
	//sem_post(supervised_philo->generic_data->check_sem);
	if (supervised_philo->generic_data->num_of_philos <= 2)
	{
		//sem_post(supervised_philo->generic_data->check_sem);
		sem_post(supervised_philo->generic_data->forks_sem);
	}
}

/*
Function to check time left for the supervised philosopher and decide if it is KO.
It checks the values stored in the philo struct: if the difference between "now"
and the moment the philo "eat last time" is greater than the "time to die", 
print KO and set that philo as KO.
*/

int	ft_check_ko(t_philo *supervised_philo)
{
		//sem_wait(supervised_philo->generic_data->check_sem);
		gettimeofday(&supervised_philo->current_time, NULL);
		if (ft_capture_timestamp(supervised_philo->current_time, \
					supervised_philo->last_ate) >= supervised_philo->generic_data->time_to_die)
		{
			//sem_post(supervised_philo->generic_data->check_sem);
			sem_wait(supervised_philo->generic_data->print_sem);
			printf(COLOR_BLUE "%ld philo %d died" COLOR_RESET "\n", \
					ft_capture_timestamp(supervised_philo->current_time, \
						supervised_philo->start_time), supervised_philo->philo_num);
			ft_set_supervised_philo_as_ko(supervised_philo);
			sem_post(supervised_philo->generic_data->print_sem);
			exit(1);
		}
	return (0);
}

/* 
    Function that checks if a philo has been set as KO.
*/

int	ft_is_philo_ko(t_philo *philo)
{
	//sem_wait(philo->generic_data->check_sem);
	if (philo->philo_ko == 1)
	{
		//sem_post(philo->generic_data->check_sem);
		return (1);
	}
	//sem_post(philo->generic_data->check_sem);
	return (0);
}
