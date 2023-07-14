/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:55:36 by msintas-          #+#    #+#             */
/*   Updated: 2023/07/14 13:03:36 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// distintos exit para diferenciar
// exit sale del hijo. en este caso habria que matar los demas procesos

void *ft_supervisor(void *thread_info)
{
	t_philo	*supervised_philo;
	t_data	*data;

	supervised_philo = (t_philo *) thread_info;
	data = supervised_philo->generic_data;

	printf("soy el hilo supervisor con thread id: %lu\n", (unsigned long)supervised_philo->tid);
	printf("deberia supervisar al FILOSOFO: %d\n", supervised_philo->philo_num);
	printf("el FILOSOFO tiene este pid: %d\n", supervised_philo->real_pid);
	while (1)
	{
		usleep(500);
		//printf("dentro del while y soy %lu\n", (unsigned long)supervised_philo->tid);
		if (ft_check_meals(supervised_philo) == 1)
			return (NULL); 
			// que no devuelva NULL, sino un numero para saber que ha ocurrido
			// si hay un ko o si han comido. tiene que ser diferente si pasa una cosa u otra
			// porque lo que hago despues es diferente, si es ko mato todo (en el principal)
			// que sea exit (0)
		if (ft_check_ko(supervised_philo) == 1)
		{
			printf("ha habido un ko: %d\n", supervised_philo->philo_num);
			return (NULL); // si hace falta return null
			// porque esto es un hilo paralelo a la rutina del hijo ft_action
			// donde hago el JOIN de esto
		}
	}
	return (NULL);
}

/* 
    Every process will execute this routine in an infinite loop. 
	It will end only when a philo is KO.
	Create one thread per process to act as supervisor and check if simulation 
	should continue running.
*/

void	*ft_action(void *each_philo)
{
	t_philo	*philo;
	int result;

	philo = (t_philo *)each_philo;
	// hilo supervisor
	printf("creo un hilo supervisor del proceso: %d\n", philo->real_pid);
	result = pthread_create(&philo->tid, NULL, &ft_supervisor, philo);
	printf("philo num %d in action\n", philo->philo_num);
	if (result != 0)
		exit (1);
	while (1)
	{
		if (ft_philo_eats(philo) == 1)
		{
			exit(1);
		}
		if (ft_philo_sleeps(philo) == 1)
		{
			exit(1);
		}
		ft_philo_thinks(philo);
	}
	// a partir de aqui no llega , este join sacarlo al main
	result = pthread_join(philo->tid, NULL);
	printf("aqui no llega!!! no hace el join");
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
	Get the id of each process to identify it later when doing kill.
*/

void	ft_create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philosophers[i].philo_num % 2 != 0)
			usleep(40);
			
		data->philosophers[i].pid = fork();
		if (data->philosophers[i].pid < 0)
		{
			printf("error forking\n");
			exit (1); // ? si hay error en uno, destruir los demas con kill
		}
		else if (data->philosophers[i].pid == 0)
		{
			// CHILD PROCESS
			printf("Child process pid from the fork return: %d\n", data->philosophers[i].pid);
			data->philosophers[i].real_pid = getpid();
			printf("Child process real_id: %d -id =  %d\n", data->philosophers[i].real_pid, i);
			
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
				kill(data->philosophers[i].real_pid, SIGINT);
				printf("ha habido un sigterm\n");
				// break ..... con kill terminamos todos los procesos? o solo 1
				i++;
			}
		}
		i++;
	}
}
