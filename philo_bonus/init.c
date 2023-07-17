/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:12:28 by msintas-          #+#    #+#             */
/*   Updated: 2023/07/14 18:48:37 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    Initialize generic data for the program. 
    If any of the values is not appropiate the program will not run.
*/

int	ft_init_data(int argc, char **argus, t_data *data)
{
	data->num_of_philos = ft_atoi(argus[0]);
	data->num_of_forks = data->num_of_philos;
	data->philosophers = malloc(sizeof(t_philo) * data->num_of_philos);
	if (data->philosophers == NULL)
		return (1);
	data->time_to_die = ft_atoi(argus[1]);
	data->time_to_eat = ft_atoi(argus[2]);
	data->time_to_sleep = ft_atoi(argus[3]);
	if (argc == 6)
	{
		data->num_must_eat = ft_atoi(argus[4]);
		if (data->num_must_eat <= 0)
			return (1);
	}
	if (data->num_of_philos < 1 || data->time_to_die < 1 \
			|| data->time_to_eat < 1 || data->time_to_sleep < 1)
		return (1);
	return (0);
}

/*
Initialize specific data for each philosopher. Assign each philosopher a number, 
starting from 1. Connect the "philo struct" with the "data struct" to have access
from each process to the main program data and fill this pointer with struct data.
*/

void	ft_init_philos(int argc, t_data *data)
{
	int	i;

	i = 0;
	
	while (i < data->num_of_philos)
	{
		data->philosophers[i].philo_num = i + 1;
		data->philosophers[i].generic_data = data;
		gettimeofday(&data->philosophers[i].start_time, NULL);			
		data->philosophers[i].last_ate = data->philosophers[i].start_time;	
		data->philosophers[i].philo_ko = 0;
		data->philosophers[i].meals = -1;
		if (argc == 6)
		{
			data->philosophers[i].meals = 0;
		}
		data->philosophers[i].finished = 0;
		i++;
	}
}

/* 
Create all semaphores. Init their values to 1, so first process with sem_wait() 
will decrease to 0 the semaphore value and all other processes may wait for a sem_post()
Forks semaphore will init with the total number of forks available.
*/

void	ft_init_semaphores(t_data *data)
{
		sem_unlink("/forks_sem");
		sem_unlink("/print_sem");
		data->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, data->num_of_forks);
		data->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
}

/* 
	Destroy mutexes
*/

void	ft_close_semaphores(t_data *data)
{
		sem_close(data->forks_sem);
		sem_close(data->print_sem);
		sem_unlink("/forks_sem");
		sem_unlink("/print_sem");
}
/* 
	Free memory to avoid leaks 
*/

void	ft_free_resources(t_data *data)
{
	free(data->philosophers);
}
