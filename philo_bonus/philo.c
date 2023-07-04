/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:55:36 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/22 13:44:47 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
    Every thread will execute this routine. Infinite loop will end only when
    a philo is ko (actions return 1).
*/

void	*ft_action(void *each_philo) // no se si este prototipo puede quedar asi
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

	i = 0;
	while (i < data->num_of_philos)
	{
		/*if (data->philosophers[i].philo_num % 2 != 0)
			usleep(40);*/
		gettimeofday(&data->philosophers[i].start_time, NULL);
		data->philosophers[i].last_ate = data->philosophers[i].start_time;
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
			ft_action(&data->philosophers[i]);
		}
		else
		{
			// PARENT PROCESS
			printf("soy el parent process: %d\n", getpid());
		}
		i++;
	}
	while (1)
	{
		usleep(500);
		if (ft_check_meals(data) == 1)
			return ;
		if (ft_check_ko(data) == 1)
			return ;
	}
	return ;
}

/* Joining threads. On success, pthread_join returns 0 */

void	ft_waitpid_processes(t_data *data)
{
	int	i;
	int	result;

	i = 0; // -1 ??
	while (i < data->num_of_philos)
	{
		waitpid(data->philosophers[i].pid, &result, 0);
		//result = pthread_join(data->philosophers[i].tid, NULL);
		if (result != 0) // aqui hace cosas distintas con kill y sigterm
		{
			ft_putstr_fd("Failed to join the thread.\n", 2);
			exit (1);
		}
		i++;
	}
}
