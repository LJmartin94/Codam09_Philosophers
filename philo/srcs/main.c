/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:13:22 by lindsay       #+#    #+#                 */
/*   Updated: 2021/09/29 14:48:39 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// // copied code START
// #include <stdio.h>
// #include <stdlib.h>
// #include <assert.h>
// #include <unistd.h>
// #include <errno.h>

// void *perform_work(void *data)
// {
// 	t_data *d;

// 	d = (t_data *)data;
// 	pthread_mutex_lock(d->id_mutex);
// 	d->this_thread++;
// 	int index = (d->this_thread);
// 	// int sleep_time = 1 + rand() % (d->number_of_philosophers);
// 	printf("THREAD %d: Started.\n", index);
// 	int sleep_time = 43 - d->this_thread;
// 	pthread_mutex_unlock(d->id_mutex);
// 	printf("THREAD %d: Will be sleeping for %d seconds.\n", index, sleep_time);
// 	sleep(sleep_time);
// 	printf("THREAD %d: Ended.\n", index);
// 	return(data);
// }
// // copied code END

void	*ft_philosophise(void *args)
{
	t_data	*d;
	int		thread_id;
	int		philosopher;

	d = ((t_philo_thread_args *)args)->d;
	thread_id = ((t_philo_thread_args *)args)->thread_id;
	philosopher = thread_id + 1;
	// FREE ARG MALLOC HERE, SET TO NULL
	while (1)
	{
		printf("Philosopher %d is idling\n", philosopher);
		usleep(100);
	}
	return (args);
}

int	main(int argc, char **argv)
{
	t_data	d;
	int		this_thread;

	ft_data_null(&d);
	if (ft_error_checker(argc, argv, &d)) //sanitise input
		return (1);
	ft_malloc_all(&d);
	ft_create_all_mutexes(&d);
	this_thread = 0;
	while (this_thread < d.number_of_philosophers)
	{
		(d.args[this_thread]).thread_id = this_thread;
		(d.args[this_thread]).d = &d;
		printf("IN MAIN: Creating thread %d.\n", this_thread);
		pthread_create(&(d.philosophers[this_thread]), NULL, \
		ft_philosophise, &((d.args)[this_thread]));
		usleep(100);
		this_thread++;
	}
	printf("IN MAIN: All threads are created.\n");
	ft_destroy_all_mutexes(&d);
	if (printf("MAIN program has ended.\n"))
		return (0);
	else
		return (0);
}
