/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:55:36 by msintas-          #+#    #+#             */
/*   Updated: 2023/07/14 18:55:20 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_supervisor(void *thread_info)
{
	t_philo	*supervised_philo;
	t_data	*data;

	supervised_philo = (t_philo *) thread_info;
	data = supervised_philo->generic_data;
	while (1)
	{
		usleep(500);
		if (ft_check_meals(supervised_philo) == 1)
		{
			return (NULL);
		}
		if (ft_check_ko(supervised_philo) == 1)
		{
			return (NULL);
		}
	}
	return (NULL);
}

/* 
    Every process will execute this routine in an infinite loop. 
	It will end only when a philo is KO.
	Create one thread per process to act as supervisor and check if simulation 
	should continue running.
*/

void	*ft_action(void *each_philo)
{
	t_philo	*philo;
	int result;

	philo = (t_philo *)each_philo;
	result = pthread_create(&philo->tid, NULL, &ft_supervisor, philo);
	if (result != 0)
		exit (1);
	while (1)
	{
		if (ft_philo_eats(philo) == 1)
		{
			pthread_join(philo->tid, NULL);
			exit(1);
		}
		if (ft_philo_sleeps(philo) == 1)
		{
			pthread_join(philo->tid, NULL);
			exit(1);
		}
		ft_philo_thinks(philo);
	}
	return (NULL);
}

/* 
    Function to fork the main process and create child processes, one per philosopher.
	Only child processes execute the routine.
	Get the id of each process to identify it later when doing kill.
*/

void	ft_create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philosophers[i].philo_num % 2 != 0)
			usleep(40);
		data->philosophers[i].pid = fork();
		if (data->philosophers[i].pid < 0)
		{
			ft_putstr_fd("Failed to fork the process.\n", 2);
			exit (1);
		}
		else if (data->philosophers[i].pid == 0)
		{
			data->philosophers[i].real_pid = getpid();			
			ft_action(&data->philosophers[i]);
		}
		i++;
	}
	return ;
}

/* 
	Function to wait for the termination of any child process (-1) in a parent process.
	Waitpid--> -1 indicates parent waits for ANY child process to terminate)
	status: when value is 0 indicates child process terminated succesfully.

*/

void	ft_waitpid_processes(t_data *data)
{
	int	i;
	int	status;
	int terminated_child;
	
	i = 0;
	terminated_child = waitpid(-1, &status, 0);
	while (i < data->num_of_philos)
	{
		if(terminated_child != data->philosophers[i].pid)
		{
			kill(data->philosophers[i].pid, SIGINT);
		}
		i++;
	}
}