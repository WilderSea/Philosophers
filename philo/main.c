/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:02:22 by msintas-          #+#    #+#             */
/*   Updated: 2023/07/17 12:14:40 by msintas-         ###   ########.fr       */
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

/* Check if the arguments passed to the program are digits */

void	ft_check_digits(unsigned int index, char *argu)
{
	(void)index;
	if (!ft_isdigit(*argu))
	{
		ft_print_usage();
	}
}

/*
    Inside the loop, the function iterates through each argument
    and performs a check in every index.
*/

void	ft_check_args(int argc, char **argus)
{
	int	i;

	i = 0;
	if (argc >= 5 && argc <= 6)
	{
		while (i < argc)
		{
			ft_striteri(argus[i], ft_check_digits);
			i++;
		}
	}
	else
	{
		ft_print_usage();
	}
}

/* Check system leaks: atexit(check_leaks) */

/*void	check_leaks(void)
{
	system("leaks -q philo");
}*/

/* 
Initializes program data and threads, waits for completion, and cleans up 
resources. Returns 0 to indicate successful execution.
*/

int	main(int argc, char **argv)
{
	t_data	data;

	ft_check_args(argc, &argv[1]);
	if (ft_init_data(argc, &argv[1], &data) == 1)
	{
		ft_print_usage();
	}
	ft_init_philos(argc, &data);
	ft_init_mutexes(&data);
	ft_create_philos(&data);
	ft_join_threads(&data);
	ft_destroy_mutexes(&data);
	ft_free_resources(&data);
	return (0);
}
