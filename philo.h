/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:02:16 by msintas-          #+#    #+#             */
/*   Updated: 2023/05/30 13:40:19 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

/* hace falta una variable que cuente el tiempo desde el principio */
    
/* time to die: si llega a pasar este tiempo desde el inicio del programa
o desde la ultima vez que comio, se muere.*/
//pthread_mutex_t *forks_array; // an array of mutex-like objects or pointers to mutexes
    //int numero_de_filo; // temp para probar
    //pthread_mutex_t *mutexes; // array de mutexes
    // pthread_mutex_t mutexes[num_of_philos];
    
    
    /*
        BONUS
        an array of forks
        represented as semaphores
        tipo de variable: semaphore
        semaphore chopstick[5];
        this chopsticks can have only two values: 0 or 1
                                not available / available
        binary semaphores
        1 means available
        0 means holded by some process
    */




/*
 struct to gather specific info about a philosopher
 */
typedef struct s_philo
{
    int philo_num; // numero de filosofo, 0, 1, 2, 3
    /* Cada filósofo tendrá asignado un número del 1 al number_of_philosophers...
    ...no puede entonces empezar por 0 */
    pthread_t tid; // identificador unico de este hilo

    int fork_left; // tenedor izquierdo
    int fork_right; // tenedor derecho

    struct s_data *generic_data; // accediendo al struct data
   
   //long int timestamp_in_ms;
    // temporal, no se como usarlo todavia
    //long int current_time;
    //long int time_spent_eating;
    
}   t_philo;


/* Struct for generic info about the simulation */

typedef struct s_data
{
    int num_of_philos;
    int num_of_forks; // num of mutexes
    
    t_philo *philosophers; // array de filosofos
    
    pthread_mutex_t *mutexes; // array de mutexes
    
    struct timeval start_time; // accedo al struct de time.h que permite coger timestamp 
    struct timeval current_time; // accedo al struct de time.h que permite coger timestamp 
    
    /* time limits */
    long int time_to_die;
    long int time_to_eat; 
    long int time_to_sleep;
    int num_must_eat; // optional
    
}   t_data;


int         ft_atoi(const char *str);
int         ft_create_philos(t_data *data);
void	    ft_putstr_fd(char *s, int fd);
long int	ft_long_atoi(const char *str);


#endif