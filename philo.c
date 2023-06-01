/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:55:36 by msintas-          #+#    #+#             */
/*   Updated: 2023/05/31 16:03:47 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* pseudocodigo para un filosofo cuando quiere comer */
/* con semaforos -- BONUS */
/*
    philosopher i
    
    do
    {
        wait(chopstick[i]);
        wait(chopstick[i + 1] % num_of_forks)
        ...
        // eat
        signal(chopstick[i]);
        signal(chopstick[i + 1] % num_of_forks)
        // think
    }
    

*/

/*

1º--> saber como se utiliza gettimeofday() function
2º--> para que se usa usleep()
3º--> pensar como calcular el tiempo que tienen que estar ejecutando
cada accion cada filosofo. como mido el tiempo que comen, 
para que dejen de comer y duerman, etc
xº --> mirar esto: 
https://stackoverflow.com/questions/52106452/have-a-function-run-for-a-specific-amount-of-time-in-c

*/


/* 
all threads will start executing this function.
it means all philosophers want to eat when the program starts
pero no se puede porque tiene que haber tenedores libres
asi que hay que separar quien empieza comiendo (pares)
y quien empieza pensando (impares)
*/


void ft_philo_thinks(t_philo *philo)
{
    //printf("philo num %d is thinking\n ", philo_num);
}

void ft_philo_sleeps(t_philo *philo)
{
    printf("timestamp philo %d starts to sleep\n", philo->philo_num);
    usleep(philo->generic_data->time_to_sleep * 1000); // para que sean microsegundos
}

// function to execute for a period of time [time_to_eat]
void ft_philo_eats(t_philo *philo)
{
    printf("timestamp philo %d is eating\n", philo->philo_num);
    // mientras que [time_to_eat] no se agote, el filosofo come
    usleep(philo->generic_data->time_to_eat * 1000); // para que sean microsegundos
    // timestamp_in_ms X is eating
}

/*

aqui los filosofos entran en accion. 
tienen que comer antes de que se agote el tiempo

*/
void *ft_action(void *each_philo)
{
    t_philo *philo;
    
    philo = (t_philo *)each_philo; // castear el nuevo struct
    
    philo->tid = pthread_self(); // Para coger el id del thread
    
    //printf("filosofo/thread num: %d with id: %lu is starting and my forks are %d and %d\n", philo->philo_num, (unsigned long)philo->tid, philo->fork_left, philo->fork_right);
   
    /* aqui los filosofos tienen que comer, dormir y pensar para siempre */
    /*while(true)
    {
        
    }*/
    
    // Lock the corresponding mutex
    // aqui el philosofo tiene que bloquear los dos mutex que le corresponden
    
    pthread_mutex_lock(&(philo->generic_data->mutexes[philo->fork_left]));
    pthread_mutex_lock(&(philo->generic_data->mutexes[philo->fork_right]));
    
    // Critical section: Access the shared resource
    gettimeofday(&philo->generic_data->current_time, NULL); // Get the current time
    //ft_elapsed_time()
    printf("%ld philo %d has taking left fork %d\n", philo->generic_data->current_time.tv_sec * 1000, philo->philo_num, philo->fork_left);
    printf("%ld philo %d has taking right fork %d\n", philo->generic_data->current_time.tv_sec, philo->philo_num, philo->fork_right);
    ft_philo_eats(philo);
    
    // Release the lock
    pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_left]);
    pthread_mutex_unlock(&philo->generic_data->mutexes[philo->fork_right]);
    printf("timestamp philo %d leaves the left fork %d\n", philo->philo_num, philo->fork_left);
    printf("timestamp philo %d leaves right fork %d\n", philo->philo_num, philo->fork_right);
        
    ft_philo_sleeps(philo);
    
    printf("Philosofo/Thread num: %d is exiting...\n", philo->philo_num);
    
    pthread_exit(NULL);
    
}


int ft_create_philos(t_data *data)
{
    int i;
    int result;
   
    // Initialize mutexes
    i = 0;
    while(i < data->num_of_philos)
    {
        pthread_mutex_init(&data->mutexes[i], NULL);
        printf("mutex number: %d is initialized\n", i);
        i++;   
    }

    // Create threads
    i = 0; // este se queda 0 porque es el indice del array
    while(i < data->num_of_philos)
    {
        printf("philo num: %d\n", data->philosophers[i].philo_num);
        result = pthread_create(&data->philosophers[i].tid, NULL, &ft_action, &data->philosophers[i]);
        if (result != 0) // on success, pthread_create returns 0
        {
            ft_putstr_fd("Failed to create thread.\n", 2);
            exit (1);
        }
        i++;   
    }

    // Wait for the threads to finish
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

    // Destroy mutexes
    i = 0;
    while(i < data->num_of_philos)
    {
        pthread_mutex_destroy(&data->mutexes[i]);
        printf("mutex number: %d is destroyed\n", i);
        i++;
    }
    
    printf("All threads have completed\n");
    
    return (0);
}