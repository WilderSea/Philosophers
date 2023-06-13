/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:55:36 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/13 12:24:30 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_philo_thinks(t_philo *philo)
{
    ft_right_now(philo);
    //pthread_mutex_lock(&philo->write_mutex);
    printf(COLOR_MAGENTA "%ld philo num %d is thinking" COLOR_RESET "\n ", philo->timestamp_in_ms, philo->philo_num);
    //pthread_mutex_unlock(&philo->write_mutex);
}


int ft_philo_sleeps(t_philo *philo)
{
    ft_right_now(philo);
    //pthread_mutex_lock(&philo->write_mutex);
    printf(COLOR_RED "%ld philo %d starts to sleep" COLOR_RESET "\n", philo->timestamp_in_ms, philo->philo_num);
    //pthread_mutex_unlock(&philo->write_mutex);
    ft_usleep_philo(philo, philo->generic_data->time_to_sleep);
    if (ft_philo_ko(philo) == 1)
        return (1);
    return (0);
}


int ft_philo_eats(t_philo *philo)
{
    pthread_mutex_lock(&(philo->generic_data->mutexes[philo->fork_left]));
    if (ft_philo_ko(philo) == 1)
    {
        pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_left]);
        return (1);
    }
    pthread_mutex_lock(&(philo->generic_data->mutexes[philo->fork_right]));
    if (ft_philo_ko(philo) == 1)
    {
        pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_left]);
        pthread_mutex_unlock(&(philo->generic_data->mutexes[philo->fork_right]));
        return (1);
    }
    ft_right_now(philo);
    
    printf("%ld philo %d has taking left fork %d\n", philo->timestamp_in_ms, philo->philo_num, philo->fork_left);
    printf("%ld philo %d has taking right fork %d\n", philo->timestamp_in_ms, philo->philo_num, philo->fork_right);
    
    ft_right_now(philo);
    
    printf(COLOR_GREEN "%ld philo %d is eating" COLOR_RESET "\n", philo->timestamp_in_ms, philo->philo_num);
    
    ft_usleep_philo(philo, philo->generic_data->time_to_eat); 
    
    pthread_mutex_lock(&philo->current_time_mutex);
    gettimeofday(&philo->current_time, NULL);
    pthread_mutex_lock(&philo->last_ate_mutex);
    philo->last_ate = philo->current_time;
    pthread_mutex_unlock(&philo->current_time_mutex);
    pthread_mutex_unlock(&philo->last_ate_mutex);
    
    if (ft_philo_ko(philo) == 1)
    {
        pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_left]);
        pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_right]);
        return (1);
    }
    pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_left]);
    pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_right]);
    if (ft_philo_ko(philo) == 1)
        return (1);
    return (0);
}

void *ft_action(void *each_philo)
{
    t_philo *philo;
    
    philo = (t_philo *)each_philo;
    
    printf("filosofo/thread id: %lu is starting\n", (unsigned long)philo->tid);

    // mientras que ningun philo este ko, seguir con la simulacion
    while(1) // este while tiene que poder detenerse de alguna forma para llegar al ultimo null
    // while (simulation is running) y cuando alguien muera, que se acabe la simulacion
    // marcar la simulacion como que ha terminado
    // tener en cuenta numero de comidas
    {
        //printf("philo ko or not: %d\n", philo->philo_ko);
        if (ft_philo_eats(philo) == 1)
        {
            printf("philo %d return null\n", philo->philo_num);
            return (NULL); // despues de aqui, este hilo llega al join
        }
        if (ft_philo_sleeps(philo) == 1) 
        {
          printf("2philo %d return null\n", philo->philo_num);
            return (NULL);
        }
        ft_philo_thinks(philo);   
    }
    printf("Philosofo/Thread num: %d is exiting...\n", philo->philo_num);
    return (NULL); // si desactivo el while, todos los hilos terminan aqui
}


void ft_create_philos(t_data *data)
{
    int i;
    int result; 

    // Create threads
    i = 0; // este se queda 0 porque es el indice del array
    while(i < data->num_of_philos)
    {
        // comprobar pares o impares e iniciar unos despues que otros
        if (data->philosophers[i].philo_num % 2 != 0)
        {
            usleep(40);
        } // aqui todavia no hace falta mutex porque no es un hilo, es main process
        gettimeofday(&data->philosophers[i].start_time, NULL);
        data->philosophers[i].last_ate = data->philosophers[i].start_time;
        result = pthread_create(&data->philosophers[i].tid, NULL, &ft_action, &data->philosophers[i]);
        printf("CREATE: philo num: %d thread id: %ld\n", data->philosophers[i].philo_num, (unsigned long)data->philosophers[i].tid);
        if (result != 0) // on success, pthread_create returns 0
        {
            ft_putstr_fd("Failed to create thread.\n", 2);
            exit (1);
        }
        i++;   
    }

    /* main thread continues executing the code that follows the pthread_create 
    call without waiting for the newly created threads to finish its execution */

    /* Bucle infinito para acceder al struct de cada filo ( y no ha cada thread ) 
    para comprobar el valor de la variable que dice si está ko */
    
    while(1)
    {
        usleep(500); // retrasar un poco la ejecución de este while
        // 1º check if philosophers ate specific number of times

        // 2º check if any philosopher died
        if (ft_checker(data) == 1)  // ESTO podria ser un extra thread, en vez de una funcion
        {
            
            // terminar programa
            ft_join_threads(data);
            //printf("philo num: %d thread id: %ld\n", data->philosophers[i].philo_num, (unsigned long)data->philosophers[i].tid);
            //pthread_join(data->philosophers[i].tid, NULL);
            
            return ;
        }
    }
    
    return ;
}

void ft_join_threads(t_data *data)
{
    int i;
    int result;   
    
    i = 0;
    while(i < data->num_of_philos)
    {
        
        printf("JOIN: philo num: %d thread id: %ld\n", data->philosophers[i].philo_num, (unsigned long)data->philosophers[i].tid);
        
        result = pthread_join(data->philosophers[i].tid, NULL);
        if (result != 0) // on success, pthread_join returns 0
        {
            ft_putstr_fd("Failed to join the thread.\n", 2);
            exit (1);
        }
        i++;
    }  
    
}
