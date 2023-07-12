/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:55:36 by msintas-          #+#    #+#             */
/*   Updated: 2023/07/12 12:52:33 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_supervisor(void *thread_info)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) thread_info;
	data = philo->generic_data;

	while (1)
	{
		usleep(500);
		if (ft_check_meals(data) == 1)
			return (NULL); // que no devuelva NULL, sino un numero para saber que ha ocurrido
			// si hay un ko o si han comido. tiene que ser diferente si pasa una cosa u otra
			// porque lo que hago despues es diferente, si es ko mato todo (en el principal)
			// que sea exit (0)
		if (ft_check_ko(data) == 1)
			return (NULL); // que sea exit (1)
			// distintos exit para diferenciar
			// exit sale del hijo. en este caso habria que matar los demas procesos
	}
	return (NULL);
}

/* 
    Every process will execute this routine in infinite loop.
	Create one thread per process to act as supervisor and check if simulation 
	should continue running.
	Infinite loop will end only when a philo is ko (actions return 1).
*/

void	*ft_action(void *each_philo)
{
	t_philo	*philo;
	int result;

	philo = (t_philo *)each_philo;
	// hilo supervisor
	result = pthread_create(&philo->tid, NULL, &ft_supervisor, &philo);
	if (result != 0)
		exit (1);
	while (1)
	{
		if (ft_philo_eats(philo) == 1)
		{
			// no tiene sentido null. exit (1) puede ser exit (0)
			// exit() terminate a process and return an "exit status" to its parent process. 
			// to indicate that it has finished its execution
			exit(1);
		}
		if (ft_philo_sleeps(philo) == 1)
		{
			return (NULL); // no tiene sentido null. exit (1) 
		}
		ft_philo_thinks(philo);
	}
	// a partir de aqui no llega , este join sacarlo al main
	result = pthread_join(philo->tid, NULL); 
	if (result != 0)
	{
		ft_putstr_fd("Failed to join the thread.\n", 2);
		exit (1);
	}
	return (NULL);
}

/* 
    Function to fork the main process and create child processes, one per philosopher.
	Only child processes execute the routine.
*/

void	ft_create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		/*if (data->philosophers[i].philo_num % 2 != 0)
			usleep(40);*/
		gettimeofday(&data->philosophers[i].start_time, NULL);
		data->philosophers[i].last_ate = data->philosophers[i].start_time;
		data->philosophers[i].pid = fork();
		if (data->philosophers[i].pid < 0)
		{
			printf("error forking\n");
			exit (1); // ? si hay error en uno, destruir los demas con kill
		}
		else if (data->philosophers[i].pid == 0)
		{
			// CHILD PROCESS
			//printf("Child process real id: %d\n", getpid());
			//printf("Child process id: %d\n", data->philosophers[i].pid);
// importante. tengo que guardar el process id del proceso, aunque sea hijo, getpid no es 0
// y ese id me sirve para luego hacer los kill, porque es el identificador real de ese proceso
			data->philosophers[i].real_pid = getpid();
			
			ft_action(&data->philosophers[i]);
		}
		else
		{
			// PARENT PROCESS
			printf("soy el parent process: %d\n", getpid());
			
		}
		i++;
	}
	return ;
}

/* 
Function to wait for the termination of any child process (-1) in a parent process.
Waitpid--> -1 indicates parent waits for ANY child process to terminate)
			Status: when value is 0 indicates child process terminated succesfully.

*/

void	ft_waitpid_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_of_philos)
	{
		printf("ha entrado en un waitpid\n");
		waitpid(-1, &status, 0);
		printf("pid value of terminated child %d\n", data->philosophers[i].pid);
		printf("real_pid value of terminated child %d\n", data->philosophers[i].real_pid);
		// cuando algun child process termine not succesful (que se corte porque muera un filosofo??)

		// status 0 seria que han comido bien y no hace falta hacer el kill porque salen todos con exit(0)
		// 
		// pero si no es 0, alguno esta ko. asi que hay que seguir con el bucle y kill todos los demas
		if (status != 0)
		{
			i = 0;
			while (i < data->num_of_philos)
			{
				kill(data->philosophers[i].real_pid, SIGTERM);
				printf("ha habido un sigterm\n");
				// break ..... con kill terminamos todos los procesos? o solo 1
				i++;
			}
		}
		i++;
	}
}
