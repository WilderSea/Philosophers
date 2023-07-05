/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:55:36 by msintas-          #+#    #+#             */
/*   Updated: 2023/07/05 17:11:26 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*void *ft_supervisor(void *thread_info)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) thread_info;
	data = philo->generic_data;
	
}*/

/* 
    Every thread will execute this routine. Infinite loop will end only when
    a philo is ko (actions return 1).
*/

void	*ft_action(void *each_philo)
{
	t_philo	*philo;
	//int result;

	philo = (t_philo *)each_philo;
	// aqui debe ir el hilo supervisor
	/*result = pthread_create(&philo->tid, NULL, &ft_supervisor, &philo);
	if (result != 0)
		exit (1);*/
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
			//printf("Child process real id: %d\n", getpid());
			//printf("Child process id: %d\n", data->philosophers[i].pid);
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

/* 
Function to wait for the termination of any child process (-1) in a parent process.
Waitpid--> -1 indicates parent waits for ANY child process to terminate)
			Status: when value is 0 indicates child process terminated succesfully.

*/

void	ft_waitpid_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_of_philos)
	{
		printf("ha entrado en un waitpid\n");
		waitpid(-1, &status, 0);
		printf("pid value of terminated child %d\n", data->philosophers[i].pid);
		// cuando algun child process termine not succesful (que se corte porque muera un filosofo??)
		if (status != 0)
		{
			i = 0;
			while (i < data->num_of_philos)
			{
				kill(data->philosophers[i].pid, SIGTERM);
				printf("ha habido un sigterm\n");
				// break ..... con kill terminamos todos los procesos? o solo 1
				i++;
			}
		}
		i++;
	}
}
