/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:22:20 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/01 14:01:23 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*

Function to return a timestamp in miliseconds.

*/

long int ft_capture_timestamp(struct timeval current, struct timeval start)
{
    long int timestamp;
    long int seconds;
    long int miliseconds;

    seconds = current.tv_sec - start.tv_sec;
    miliseconds = (current.tv_usec / 1000) - (start.tv_usec / 1000);
    timestamp = seconds * 1000 + miliseconds;
    return (timestamp);
}

/*

Function to measure time consumed in an action
time in milliseconds???

*/

void ft_diff_time()
{
    
}