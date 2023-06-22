/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:02:16 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/22 12:15:05 by msintas-         ###   ########.fr       */
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

/*
 Struct to gather specific info about a philosopher
 */

typedef struct s_philo
{
    int philo_num;
    int fork_left;
    int fork_right;
    int philo_ko;
    int meals;
    int finished;
    pthread_t tid;
    long int timestamp_in_ms;
    struct timeval start_time;
    struct timeval current_time;
    struct timeval last_ate;
    pthread_mutex_t current_time_mutex;
    pthread_mutex_t last_ate_mutex;
    pthread_mutex_t philo_ko_mutex;
    pthread_mutex_t meals_mutex;
    pthread_mutex_t finished_mutex;
    struct s_data *generic_data;
}   t_philo;


/* Struct for generic info about the simulation */

typedef struct s_data
{
    int num_of_philos;
    int num_of_forks;
    int num_must_eat;
    t_philo *philosophers;
    pthread_mutex_t *mutexes;
    int time_to_die;
    int time_to_eat; 
    int time_to_sleep;
    pthread_mutex_t count_mutex;
}   t_data;


/* Main functions */
int    ft_init_data(int argc, char **argus, t_data *data);
void    ft_init_philos(int argc, t_data *data);
void    ft_init_mutexes(t_data *data);
void    ft_create_philos(t_data *data);
void    ft_join_threads(t_data *data);
void    ft_destroy_mutexes(t_data *data);

/* Actions */
int ft_philo_eats(t_philo *philo);
int ft_philo_sleeps(t_philo *philo);
void ft_philo_thinks(t_philo *philo);

/* Time functions */
long int ft_capture_timestamp(struct timeval current, struct timeval start);
void ft_right_now(t_philo *philo);
void ft_usleep_philo(t_philo *philo, long int waiting_time);

/* Checkers */
int ft_check_ko(t_data *data);
int ft_is_philo_ko(t_philo *philo);
void ft_set_philos_as_ko(t_data *data);

void ft_count_meals(t_philo *philo);
int ft_check_meals(t_data *data);
int ft_everyphilo_ate(t_data *data, int total);

void ft_check_args(int argc, char **argus);
void ft_check_digits(unsigned int index, char *argu);

/* Resources */
void	ft_print_usage(void);
void ft_free_resources(t_data *data);
void	check_leaks(void);

/* Utils */
int         ft_atoi(const char *str);
void	    ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int	ft_isdigit(int c);

#endif