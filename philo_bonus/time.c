/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:36:02 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/26 11:36:07 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*

    Function to return a timestamp in miliseconds.

*/

long int	ft_capture_timestamp(struct timeval current, struct timeval start)
{
	long int	timestamp;
	long int	seconds;
	long int	miliseconds;

	seconds = current.tv_sec - start.tv_sec;
	miliseconds = (current.tv_usec / 1000) - (start.tv_usec / 1000);
	timestamp = seconds * 1000 + miliseconds;
	return (timestamp);
}

/*

    Function to get the current time

*/

void	ft_right_now(t_philo *philo)
{
	pthread_mutex_lock(&philo->current_time_mutex);
	gettimeofday(&philo->current_time, NULL);
	philo->timestamp_in_ms = ft_capture_timestamp(philo->current_time, \
			philo->start_time);
	pthread_mutex_unlock(&philo->current_time_mutex);
}

/*

    Function to improve usleep default function

*/

void	ft_usleep_philo(t_philo *philo, long int waiting_time)
{
	long int	finish_wait;
	long int	now;

	pthread_mutex_lock(&philo->current_time_mutex);
	gettimeofday(&philo->current_time, NULL);
	now = ft_capture_timestamp(philo->current_time, philo->start_time);
	finish_wait = now + waiting_time;
	while (finish_wait > now)
	{
		gettimeofday(&philo->current_time, NULL);
		now = ft_capture_timestamp(philo->current_time, philo->start_time);
		if (ft_is_philo_ko(philo) == 1)
		{
			pthread_mutex_unlock(&philo->current_time_mutex);
			break ;
		}
		usleep(240);
	}
	pthread_mutex_unlock(&philo->current_time_mutex);
}
