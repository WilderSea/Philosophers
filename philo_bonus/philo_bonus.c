/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:35:48 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/28 11:50:46 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* 
    Every thread will execute this routine. Infinite loop will end only when
    a philo is ko (actions return 1).
*/

void	*ft_action(void *each_philo)
{
	t_philo	*philo;

	philo = (t_philo *)each_philo;
	while (1)
	{
		if (ft_philo_eats(philo) == 1)
		{
			return (NULL);
		}
		if (ft_philo_sleeps(philo) == 1)
		{
			return (NULL);
		}
		ft_philo_thinks(philo);
	}
	return (NULL);
}

/* 
    Function to create threads, one per philosopher. This function as a main 
    thread will continue executing an infinite loop that will check if philos 
    are still alive or they still have to eat.
*/

void	ft_create_philos(t_data *data)
{
	int	i;
	int num_of_children;

	i = 0;
	num_of_children = 0;
	while (i < data->num_of_philos)
	{
		gettimeofday(&data->philosophers[i].start_time, NULL);
		data->philosophers[i].last_ate = data->philosophers[i].start_time;
		//
		data->philosophers[i].pid = fork();
		if (data->philosophers[i].pid < 0)
		{
			printf("error forking\n");
			exit (1);
		}
		else if (data->philosophers[i].pid == 0)
		{
			// CHILD PROCESS
			printf("Child process real id: %d\n", getpid());
			printf("Child process id: %d\n", data->philosophers[i].pid);
			// enviar a hacer la rutina al child
			num_of_children++;
		}
		else
		{
			// PARENT PROCESS
			printf("soy el parent process: %d\n", getpid());
		}
		i++;
	}
	printf("numero de children: %d\n", num_of_children);

	

	/*while (1)
	{
		usleep(500);
		if (ft_check_meals(data) == 1)
			return ;
		if (ft_check_ko(data) == 1)
			return ;
	}*/
	return ;
}


/* Joining threads. On success, pthread_join returns 0 */

void	ft_join_threads(t_data *data)
{
	int	i;
	//int	result;

	i = 0;
	while (i < data->num_of_philos) // aqui va waitpid ?
	{
		//result = pthread_join(data->philosophers[i].tid, NULL);
		/*if (result != 0)
		{
			ft_putstr_fd("Failed to join the thread.\n", 2);
			exit (1);
		}*/
		i++;
	}
}
