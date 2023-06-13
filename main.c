/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:02:22 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/13 12:30:35 by msintas-         ###   ########.fr       */
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



/*void ft_check_args(int argc, char **argus, t_data *data)
{
    if (argc >= 5 && argc <= 6)
    {
        // hacer un bucle que pase por cada argc
        // y lo compruebe, que son numeros y no letras, etc
        
    }
    else
    {
        ft_print_usage();
    }
}*/

/*

    bucle que compruebe la diferncai entre la ultima vez que comio y ahora.
    Este bucle comprueba todos los filosofos estan vivos. Si uno muere, establece
    some_philos_ko a 1 para que los demas mueran. Es aconsejable hacer un join a todos los

*/


int main(int argc, char **argv)
{
    
    t_data  data;
    
    //ft_check_args(argc, &argv[1], &data); // TO DO **

    ft_init_data(argc, &argv[1], &data); // init generic data

    ft_init_philos(&data); // init data para cada philosofo

    ft_init_mutexes(&data); // init all mutexes

    ft_create_philos(&data); // create threads

    ft_join_threads(&data);

    ft_destroy_mutexes(&data);

    // free memory

    printf("All threads have completed\n");
    


    return (0);
}

