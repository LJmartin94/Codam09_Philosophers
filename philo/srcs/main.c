/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:13:22 by lindsay       #+#    #+#                 */
/*   Updated: 2021/09/20 18:04:40 by limartin      ########   odam.nl         */
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

void *ft_philosophise(void *args)
{
	t_data *d;
	int thread_id;
	int philosopher;
	
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

int main(int argc, char **argv)
{
	t_data d;
	pthread_t *philosophers; // array of 'philosopher' threads
	t_philo_thread_args *args; // array of args passed to philosopher threads
	pthread_mutex_t modify_data; // mutex reuired to change any data in the data struct d
	int this_thread;
	
	if (ft_error_checker(argc, argv, &d)) //sanitise input
		return (1);
	
	philosophers = (pthread_t *)malloc(sizeof(pthread_t) * d.number_of_philosophers); //malloc philo array
	args = (t_philo_thread_args *)malloc(sizeof (t_philo_thread_args) * d.number_of_philosophers); //malloc philo args
	d.game_state = &modify_data; //save location of mutex for modifying data struct to data struct
	
	if (pthread_mutex_init(d.game_state, NULL))
	{
		perror("errno on mutex init: ");
		return(errno); // NEED PROPER ERROR MESSAGE HERE
	}

	this_thread = 0;

	while (this_thread < d.number_of_philosophers)
	{
		(args[this_thread]).thread_id = this_thread;
		(args[this_thread]).d = &d;
		printf("IN MAIN: Creating thread %d.\n", this_thread);
		pthread_create(&philosophers[this_thread], NULL, ft_philosophise, &(args[this_thread]));
		usleep(100);
		this_thread++;
	}

	printf("IN MAIN: All threads are created.\n");
	
	// // copied code START
	// pthread_t threads[d.number_of_philosophers];
	// // int thread_args[d.number_of_philosophers];
	// int i;
	// int result_code;
	// pthread_mutex_t philo_mutex;

	// d.id_mutex = &philo_mutex;

	// if (pthread_mutex_init(d.id_mutex, NULL))
	// {
	// 	perror("errno on mutex init: ");
	// 	return(errno); // NEED PROPER ERROR MESSAGE HERE
	// }
	// // write (1, "Bussin'\n", 8);

	// d.this_thread = 0;

	// //create all threads one by one
	// for (i = 0; i < d.number_of_philosophers; i++)
	// {
	// 	printf("IN MAIN: Creating thread %d.\n", i + 1);
	// 	result_code = pthread_create(&threads[i], NULL, perform_work, &d);
	// 	// assert(!result_code);
  	// }

  	// printf("IN MAIN: All threads are created.\n");

	// //wait for each thread to complete
	// for (i = 0; i < d.number_of_philosophers; i++) 
	// {
	// 	result_code = pthread_join(threads[i], NULL);
	// 	// assert(!result_code);
	// 	printf("IN MAIN: Thread %d has ended.\n", i + 1);
	// }

	// if (pthread_mutex_destroy(d.id_mutex))
	// {
	// 	perror("errno on mutex destroy: ");
	// 	return(errno); // NEED PROPER ERROR MESSAGE HERE
	// }

	// printf("MAIN program has ended.\n");
	// // copied code END
	
	return 0;
}

