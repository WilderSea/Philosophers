/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:02:22 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/16 16:21:00 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_usage(void)
{
	ft_putstr_fd("Usage : [program name] [number_of_philosophers] \
--in miliseconds [time_to_die] [time_to_eat] [time_to_sleep] \
--optional[number_of_times_each_philosopher_must_eat]\n", 1);
	ft_putstr_fd("Example : ./philo 15 8000 7000 6000\n", 1);
	exit(1);
}
/* 
Free memory to avoid leaks 
*/

void ft_free_resources(t_data *data)
{
    free(data->philosophers);
    free(data->mutexes);
}

/* 
Initializes program data and threads, waits for completion, and cleans up 
resources. Returns 0 to indicate successful execution.
*/

int main(int argc, char **argv)
{
    
    t_data  data;
    
    //atexit(check_leaks);
    ft_check_args(argc, &argv[1]);

    ft_init_data(argc, &argv[1], &data);

    ft_init_philos(argc, &data);

    ft_init_mutexes(&data);

    ft_create_philos(&data);

    ft_join_threads(&data);

    ft_destroy_mutexes(&data);

    ft_free_resources(&data);

    printf("All threads have completed\n");
    

    return (0);
}

