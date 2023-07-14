/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:17:56 by msintas-          #+#    #+#             */
/*   Updated: 2023/07/14 12:58:43 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Add one meal to a philosopher */

void	ft_count_meals(t_philo *philo)
{
	philo->meals++;
}

/*
    Function to check if all philosophers ate at least the required
    number of times, updating a counter. When this counter reaches the
    same number of philos, will return 1 to the supervisor thread to indicate
    simulation can stop. Also, set philo as "finished" so the 
    eat function can return 1 and the routine can exit.
*/

int	ft_check_meals(t_philo *supervised_philo)
{
	if (supervised_philo->meals >= supervised_philo->generic_data->num_must_eat)
	{
		supervised_philo->finished = 1;
		supervised_philo->generic_data->how_many_philo_ate++;
	}
	if (ft_everyphilo_ate(supervised_philo->generic_data) == 1)
		return (1);
	return (0);
}

/* Check when counter reaches the number of philos. */

int	ft_everyphilo_ate(t_data *data)
{
	if (data->how_many_philo_ate == data->num_of_philos)
	{
		return (1);
	}
	return (0);
}

/* Function to print which forks take every philo. */

void	ft_print_forks(t_philo *philo)
{
	printf("%ld philo %d has taking a fork.\n", philo->timestamp_in_ms, \
			philo->philo_num);
	printf("%ld philo %d has taking another fork\n", philo->timestamp_in_ms, \
			philo->philo_num);
}
