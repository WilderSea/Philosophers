/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:34:49 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/26 11:34:57 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_get_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->generic_data->mutexes[philo->fork_left]));
	if (ft_is_philo_ko(philo) == 1)
	{
		pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_left]);
		return (1);
	}
	pthread_mutex_lock(&(philo->generic_data->mutexes[philo->fork_right]));
	if (ft_is_philo_ko(philo) == 1)
	{
		pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_left]);
		pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_right]);
		return (1);
	}
	return (0);
}

int	ft_leave_forks(t_philo *philo)
{
	if (ft_is_philo_ko(philo) == 1)
	{
		pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_left]);
		pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_right]);
		return (1);
	}
	pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_left]);
	pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_right]);
	return (0);
}

void	ft_philo_thinks(t_philo *philo)
{
	ft_right_now(philo);
	printf(COLOR_MAGENTA "%ld philo %d is thinking" COLOR_RESET "\n", \
			philo->timestamp_in_ms, philo->philo_num);
}

int	ft_philo_sleeps(t_philo *philo)
{
	ft_right_now(philo);
	printf(COLOR_RED "%ld philo %d is sleeping" COLOR_RESET "\n", \
			philo->timestamp_in_ms, philo->philo_num);
	ft_usleep_philo(philo, philo->generic_data->time_to_sleep);
	if (ft_is_philo_ko(philo) == 1)
		return (1);
	return (0);
}

int	ft_philo_eats(t_philo *philo)
{
	if (ft_get_forks(philo) == 1)
		return (1);
	ft_right_now(philo);
	ft_print_forks(philo);
	ft_right_now(philo);
	printf(COLOR_GREEN "%ld philo %d is eating" COLOR_RESET "\n", \
			philo->timestamp_in_ms, philo->philo_num);
	ft_usleep_philo(philo, philo->generic_data->time_to_eat);
	pthread_mutex_lock(&philo->current_time_mutex);
	gettimeofday(&philo->current_time, NULL);
	pthread_mutex_lock(&philo->last_ate_mutex);
	philo->last_ate = philo->current_time;
	pthread_mutex_unlock(&philo->current_time_mutex);
	pthread_mutex_unlock(&philo->last_ate_mutex);
	if (philo->generic_data->num_must_eat > 0)
		ft_count_meals(philo);
	if (ft_leave_forks(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->finished_mutex);
	if (philo->finished == 1)
		return (1);
	pthread_mutex_unlock(&philo->finished_mutex);
	if (ft_is_philo_ko(philo) == 1)
		return (1);
	return (0);
}
