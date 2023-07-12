/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:17:56 by msintas-          #+#    #+#             */
/*   Updated: 2023/07/11 15:41:48 by msintas-         ###   ########.fr       */
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
    same number of philos, will return 1 to the main thread to indicate
    simulation can stop. Also, set every philo as "finished" so the 
    eat function can return 1 in every thread and start the joining.
*/

int	ft_check_meals(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < data->num_of_philos)
	{
		if (data->philosophers[i].meals >= data->num_must_eat)
		{
			data->philosophers[i].finished = 1;
			count++;
		}
		i++;
	}
	if (ft_everyphilo_ate(data, count) == 1)
		return (1);
	return (0);
}

/* Check when counter reaches the number of philos. */

int	ft_everyphilo_ate(t_data *data, int total)
{
	if (total == data->num_of_philos)
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
