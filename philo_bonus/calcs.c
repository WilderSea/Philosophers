/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:07:49 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/26 17:55:40 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void ft_print_array(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		printf("array pid: %d\n", data->philosophers[i].pid);
		i++;
	}
}
