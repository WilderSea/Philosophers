/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:17:56 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/15 15:09:07 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
Function to check time left for each philosopher and decide if it is KO.
It checks the values stored in each philo struct. If the difference between "now"
and the moment the philo "eat last time" is greater than the "time to die", set
the philo as KO.
*/

int ft_checker(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_of_philos) 
    {
        gettimeofday(&data->philosophers[i].current_time, NULL);
        pthread_mutex_lock(&data->philosophers[i].last_ate_mutex);
        if (ft_capture_timestamp(data->philosophers[i].current_time, data->philosophers[i].last_ate) >= data->time_to_die)
        {
            printf("%ld philo has died %i\n", ft_capture_timestamp(data->philosophers[i].current_time, data->philosophers[i].start_time), i + 1);
            printf("philo num: %d thread id: %ld\n", data->philosophers[i].philo_num, (unsigned long)data->philosophers[i].tid);
            pthread_mutex_unlock(&data->philosophers[i].last_ate_mutex);
            i = 0;
            while (i < data->num_of_philos)
            {
                pthread_mutex_lock(&data->philosophers[i].philo_ko_mutex);
                data->philosophers[i].philo_ko = 1;
                if (data->num_of_philos == 1)
                {
                    pthread_mutex_unlock(&data->mutexes[data->philosophers[i].fork_right]); 
                }
                pthread_mutex_unlock(&data->philosophers[i].philo_ko_mutex);
                i++;
            }
            return (1);
        }
        else
        {
            pthread_mutex_unlock(&data->philosophers[i].last_ate_mutex);
            i++;
        }
    }
    return (0);
}


int ft_philo_ko(t_philo *philo)
{
    pthread_mutex_lock(&philo->philo_ko_mutex);
    //printf("philo %d ko value %d\n",philo->philo_num ,philo->philo_ko );
    if (philo->philo_ko == 1)
    {
        pthread_mutex_unlock(&philo->philo_ko_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->philo_ko_mutex);
    return (0);
}

/* Discount meal to a philosopher */

void ft_count_meals(t_philo *philo)
{
    pthread_mutex_lock(&philo->meals_mutex);
    philo->meals--;
    //printf("philo num: %d still %d meals left\n", philo->philo_num, philo->meals);
    pthread_mutex_unlock(&philo->meals_mutex);
}


void ft_check_digits(unsigned int index, char *argu)
{
    if (!ft_isdigit(*argu))
    {
        ft_print_usage();
    }
    /*if (ft_isdigit(*argu))
    {
        printf("Character at index %u is a digit: %c\n", index, *argu);
        
    }*/
    else
    {
        //printf("Character at index %u is not a digit: %c\n", index, *argu);
        printf("Character at index %u is a digit: %c\n", index, *argu);
    }
}
/*
Inside the loop, the function f is called with two arguments: 
the current index i and a pointer to the current character &s[i]. 
The purpose of passing the index and the character is to allow the function f 
to perform some operation on the character based on its index.
*/

void ft_check_args(int argc, char **argus)
{
    if (argc >= 5 && argc <= 6)
    {
        int i;

        i = 0;
        while (i < argc)
        {
            printf("argc es: %s\n", argus[i]);
            ft_striteri(argus[i], ft_check_digits);
            i++;
        }
        
        
    }
    else
    {
        ft_print_usage();
    }
}

/* Check system leaks */


void	check_leaks(void)
{
	system("leaks -q philo");
}

