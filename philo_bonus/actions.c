/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:36:41 by msintas-          #+#    #+#             */
/*   Updated: 2023/07/13 18:44:04 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_forks(t_philo *philo)
{
	sem_wait(philo->generic_data->forks_sem); 
	if (ft_is_philo_ko(philo) == 1)
	{
		printf("ha habido un ko getting forks\n");
		return (1);
	}
	sem_wait(philo->generic_data->forks_sem);
	if (ft_is_philo_ko(philo) == 1)
	{
		sem_post(philo->generic_data->forks_sem);
		sem_post(philo->generic_data->forks_sem);
		printf("ha habido un ko getting forks\n");
		return (1);
	}
	return (0);
}

int	ft_leave_forks(t_philo *philo)
{
	if (ft_is_philo_ko(philo) == 1)
	{
		sem_post(philo->generic_data->forks_sem);
		sem_post(philo->generic_data->forks_sem);
		printf("ha habido un ko leaving forks\n");
		return (1);
	}
	sem_post(philo->generic_data->forks_sem);
	sem_post(philo->generic_data->forks_sem);
	printf("ha habido un ko leaving forks\n");
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
	printf("empieza rutina comida\n");
	if (ft_get_forks(philo) == 1)
		return (1);
	ft_right_now(philo);
	ft_print_forks(philo);
	ft_right_now(philo);
	printf(COLOR_GREEN "%ld philo %d is eating" COLOR_RESET "\n", \
			philo->timestamp_in_ms, philo->philo_num);
	ft_usleep_philo(philo, philo->generic_data->time_to_eat);
	gettimeofday(&philo->current_time, NULL);
	philo->last_ate = philo->current_time;
	printf("Philo num %d\n", philo->philo_num);
	if (philo->generic_data->num_must_eat > 0)
		ft_count_meals(philo);
	if (ft_leave_forks(philo) == 1)
		return (1);
	if (philo->finished == 1)
		return (1);
	if (ft_is_philo_ko(philo) == 1)
		return (1);
	return (0);
}
