/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:02:22 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/05 10:27:30 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

/*
    primer objetivo
    que la funcion que el hilo quiera ejecutar
    sea capaz de cambiar de estado (eat, sleep or think)
    por tiempo
    una vez tenga eso, hacer mas hilos y coordinar/sincronizar
    que se ejecuten las tareas con los cambios de estado acorde a cuando 
    deban ejecutarse
    
    despues miro lo de los tenedores (mutex)


*/



void	ft_print_usage(void)
{
	ft_putstr_fd("Usage : [program name] [number_of_philosophers] \
--in miliseconds [time_to_die] [time_to_eat] [time_to_sleep] \
--optional[number_of_times_each_philosopher_must_eat]\n", 1);
	ft_putstr_fd("Example : ./philo 15 8000 7000 6000\n", 1);
	exit(1);
}


// TO DO: deberia comprobar que son numeros y no letras, etc

void ft_check_args(int argc, char **argus, t_data *data)
{
    if (argc >= 5 && argc <= 6)
    {
        
        
        
    }
    else
    {
        ft_print_usage();
    }
}


void ft_init_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_of_philos)
    {
        // tiene que empezar por 1 el número de filosofo
        data->philosophers[i].philo_num = i + 1; // assign a number to each thread/philosopher
        // printf("Soy philo num: %d\n", data->philosophers[i].philo_num);
        data->philosophers[i].fork_left = i;
        data->philosophers[i].fork_right = (i + 1) % data->num_of_philos;
        data->philosophers[i].generic_data = data; 
        // muy importante. Aqui le digo que mi puntero de generic data, se llena con la info del struct data
        i++;
    }
}

// iniciar todos los valores de la simulacion
void ft_init_data(int argc, char **argus, t_data *data)
{
    data->num_of_philos = ft_atoi(argus[0]);
    data->num_of_forks = data->num_of_philos;
    printf("number of philosophers: %d\n", data->num_of_philos);
    printf("number of forks: %d\n", data->num_of_forks);
    
    data->philosophers = malloc(sizeof(t_philo) * data->num_of_philos);
    data->mutexes = malloc(sizeof(pthread_mutex_t) * (data->num_of_philos + 1));
    // falta proteger los mallocs
    data->time_to_die = ft_long_atoi(argus[1]); // tiempo limite
    //printf("time_to_die: %ld\n", data->time_to_die);
    data->time_to_eat = ft_long_atoi(argus[2]);
    //printf("time_to_eat: %ld\n", data->time_to_eat);
    data->time_to_sleep = ft_long_atoi(argus[3]);
    //printf("time_to_sleep: %ld\n", data->time_to_sleep);
    if (argc == 6)
    {
        data->num_must_eat = ft_long_atoi(argus[4]);
        //printf("must eat n of times: %d\n", data->num_must_eat);
    }
    data->some_philo_ko = 0;
    gettimeofday(&data->start_time, NULL);
}

int main(int argc, char **argv)
{
    
    t_data  data;
    
    ft_check_args(argc, &argv[1], &data); // TO DO **

    ft_init_data(argc, &argv[1], &data);

    ft_init_philos(&data);

    ft_supervisor();
    
    ft_create_philos(&data);
    
    return (0);
}

