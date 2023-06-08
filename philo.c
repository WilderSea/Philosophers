/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:55:36 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/08 13:26:37 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void ft_philo_thinks(t_philo *philo)
{
    // Get timestamp when philo starts to sleep
    ft_right_now(philo);
    printf(COLOR_MAGENTA "%ld philo num %d is thinking" COLOR_RESET "\n ", philo->timestamp_in_ms, philo->philo_num);
}


int ft_philo_sleeps(t_philo *philo)
{
    // Get timestamp when philo starts to sleep
    ft_right_now(philo);
    printf(COLOR_RED "%ld philo %d starts to sleep" COLOR_RESET "\n", philo->timestamp_in_ms, philo->philo_num);
    usleep(philo->generic_data->time_to_sleep * 1000); // para que sean microsegundos, tiempo de dormir
    //comprubar si ha muerto
    if (ft_philo_ko(philo) == 1)
        return (1);
    return (0);
}


int ft_philo_eats(t_philo *philo)
{
    pthread_mutex_lock(&(philo->generic_data->mutexes[philo->fork_left]));
    if (ft_philo_ko(philo) == 1)
        return (1);
    pthread_mutex_lock(&(philo->generic_data->mutexes[philo->fork_right]));
    if (ft_philo_ko(philo) == 1)
        return (1);
    printf("%ld philo %d has taking left fork %d\n", philo->timestamp_in_ms, philo->philo_num, philo->fork_left);
    printf("%ld philo %d has taking right fork %d\n", philo->timestamp_in_ms, philo->philo_num, philo->fork_right);
    pthread_mutex_lock(&(philo->time_mutex));
    ft_right_now(philo);
    pthread_mutex_unlock(&(philo->time_mutex));
    printf(COLOR_GREEN "%ld philo %d is eating" COLOR_RESET "\n", philo->timestamp_in_ms, philo->philo_num);
    // hacer esta funcion para tunear el "usleep" xq no es exacto
    // ft_usleep_philo(philo, philo->generic_data->time_to_eat); 
    usleep(philo->generic_data->time_to_eat * 1000); // para que sean microsegundos, tiempo que pasa comiendo
    // Get the current time cuando filosofo termino de comer por ultima vez
    pthread_mutex_lock(&philo->time_mutex);
    gettimeofday(&philo->current_time, NULL); 
    pthread_mutex_unlock(&philo->time_mutex);
    pthread_mutex_lock(&philo->last_ate_mutex);
    philo->last_ate = philo->current_time;
    pthread_mutex_unlock(&philo->last_ate_mutex);
    if (ft_philo_ko(philo) == 1)
    {
        return (1);
    }
    pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_left]);
    pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_right]);
    return (0);
}

void *ft_action(void *each_philo)
{
    t_philo *philo;
    
    philo = (t_philo *)each_philo; // castear el nuevo struct
    
    philo->tid = pthread_self(); // Para coger el id del thread
    
    //printf("filosofo/thread id: %lu is starting\n", (unsigned long)philo->tid);

    // aqui comprobar filosofos pares o impares. y hacerle un retraso al empezar
   
    /* aqui los filosofos tienen que comer, dormir y pensar para siempre */
    // mientras que ningun philo este ko, seguir con la simulacion
    while(1)
    {
        //printf("philo ko or not: %d\n", philo->philo_ko);
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
        // para los prints y las variables que se modifican (last_ate, philo_ko)
        // hay que hacer mutexes para evitar data racings
        pthread_mutex_lock(&philo->printf_mutex);
        printf("Philosofo/Thread num: %d is exiting...\n", philo->philo_num);
        pthread_mutex_unlock(&philo->printf_mutex);

        return (NULL);
}


int ft_create_philos(t_data *data)
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
        }
        gettimeofday(&data->philosophers[i].start_time, NULL); // necesita un mutex??
        data->philosophers[i].last_ate = data->philosophers[i].start_time;
        result = pthread_create(&data->philosophers[i].tid, NULL, &ft_action, &data->philosophers[i]);
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
        usleep(100); // retrasar un poco la ejecución de este while
        // 1º check if philosophers ate specific number of times

        // 2º check if any philosopher died
        i = 0;
        while(i < data->num_of_philos)
        {
            if (ft_checker(data) == 1)
            {
                printf("hay un ko\n");
                // terminar programa
                return (0);
            }
            i++;
        }
    }
    
    // Wait for the threads to finish
    // LOS JOIN deberian estar dentro de otro bucle??
    i = 0;
    while(i < data->num_of_philos)
    {
        result = pthread_join(data->philosophers[i].tid, NULL);
        if (result != 0) // on success, pthread_join returns 0
        {
            ft_putstr_fd("Failed to join the thread.\n", 2);
            exit (1);
        }
        i++;
    }  

    
    
    
    return (0);
}
