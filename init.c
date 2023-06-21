/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:12:28 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/21 14:21:33 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    Initialize generic data for the program. 
    If any of the values is not appropiate the program will not run.
*/

int ft_init_data(int argc, char **argus, t_data *data)
{
    data->num_of_philos = ft_atoi(argus[0]);
    data->num_of_forks = data->num_of_philos;
    data->philosophers = malloc(sizeof(t_philo) * data->num_of_philos);
    if (data->philosophers == NULL)
        return (1);
    data->mutexes = malloc(sizeof(pthread_mutex_t) * (data->num_of_philos));
    if (data->mutexes == NULL)
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
    if (data->num_of_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 1 \
     || data->time_to_sleep < 1) {
        return (1);
    }
    return (0);
}

/*
Initialize specific data for each thread.
Assign each philosopher a number, starting from 1, and the two nearest forks,
starting from 0. Connect the "philo struct" with the "data struct" to have access
from each thread to the main program data and fill this pointer with struct data.
*/

void ft_init_philos(int argc, t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_of_philos)
    {
        data->philosophers[i].philo_num = i + 1;
        data->philosophers[i].fork_left = i;
        data->philosophers[i].fork_right = (i + 1) % data->num_of_philos;
        data->philosophers[i].generic_data = data;
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

/* Initialize all mutexes */

void ft_init_mutexes(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_of_philos)
    {
        pthread_mutex_init(&data->mutexes[i], NULL);
        pthread_mutex_init(&data->philosophers[i].current_time_mutex, NULL);
        pthread_mutex_init(&data->philosophers[i].last_ate_mutex, NULL);
        pthread_mutex_init(&data->philosophers[i].philo_ko_mutex, NULL);
        pthread_mutex_init(&data->philosophers[i].meals_mutex, NULL);
        pthread_mutex_init(&data->philosophers[i].finished_mutex, NULL);
        i++;   
    }
    pthread_mutex_init(&data->count_mutex, NULL);
}

/* Destroy mutexes */

void ft_destroy_mutexes(t_data *data)
{
    int i;
    
    i = 0;
    while(i < data->num_of_philos)
    {
        pthread_mutex_destroy(&data->mutexes[i]);
        pthread_mutex_destroy(&data->philosophers[i].current_time_mutex);
        pthread_mutex_destroy(&data->philosophers[i].last_ate_mutex);
        pthread_mutex_destroy(&data->philosophers[i].philo_ko_mutex);
        pthread_mutex_destroy(&data->philosophers[i].meals_mutex);
        pthread_mutex_destroy(&data->philosophers[i].finished_mutex);
        printf("mutexes destroyed\n");
        i++;
    }
    pthread_mutex_destroy(&data->count_mutex);
}

/* 
Free memory to avoid leaks 
*/

void ft_free_resources(t_data *data)
{
    free(data->philosophers);
    free(data->mutexes);
}