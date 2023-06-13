/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:02:16 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/12 13:13:01 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"



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
   
    long int timestamp_in_ms;
    struct timeval last_ate; // timestamp de la ultima vez que empezo a comer

    // los timestamp deben ser especificos de cada philo
    struct timeval start_time;
    struct timeval current_time;
    
    int philo_ko; // 0 vivo, 1 muerto
    
    //pthread_mutex_t write_mutex;
    //pthread_mutex_t check_mutex;
    pthread_mutex_t last_ate_mutex;
    pthread_mutex_t current_time_mutex;
    pthread_mutex_t philo_ko_mutex;
    
}   t_philo;


/* Struct for generic info about the simulation */

typedef struct s_data
{
    int num_of_philos;
    int num_of_forks; // num of mutexes
    
    t_philo *philosophers; // array de filosofos
    
    pthread_mutex_t *mutexes; // array de mutexes
    
    /* time limits */
    long int time_to_die;
    long int time_to_eat; 
    long int time_to_sleep;
    int num_must_eat; // optional
    
    int some_philo_ko;
    //pthread_mutex_t write_mutex;
    
}   t_data;

/* utils */
int         ft_atoi(const char *str);
void	    ft_putstr_fd(char *s, int fd);
long int	ft_long_atoi(const char *str);

/*  */
void ft_init_data(int argc, char **argus, t_data *data);
void ft_init_philos(t_data *data);
void ft_create_philos(t_data *data);


/* time functions */
long int ft_capture_timestamp(struct timeval current, struct timeval start);
void ft_right_now(t_philo *philo);
void ft_usleep_philo(t_philo *philo, long int waiting_time);
int ft_checker(t_data *data); // comprueba si ha muerto y lo marca con una variable
int ft_philo_ko(t_philo *philo);
void ft_destroy_mutexes(t_data *data);
void ft_init_mutexes(t_data *data);
void ft_join_threads(t_data *data);

#endif