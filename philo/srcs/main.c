/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:13:22 by lindsay       #+#    #+#                 */
/*   Updated: 2021/06/18 16:24:34 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// copied code START
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

void *perform_work(void *arguments)
{
  int index = *((int *)arguments);
  int sleep_time = 1 + rand() % NUM_THREADS;
  printf("THREAD %d: Started.\n", index);
  printf("THREAD %d: Will be sleeping for %d seconds.\n", index, sleep_time);
  sleep(sleep_time);
  printf("THREAD %d: Ended.\n", index);
  return(arguments);
}
// copied code END

int main(int argc, char **argv)
{
	t_data d;

	if (ft_error_checker(argc, argv, &d))
		return (1);
	
	// copied code START
	pthread_t threads[NUM_THREADS];
	int thread_args[NUM_THREADS];
	int i;
	int result_code;

	//create all threads one by one
	for (i = 0; i < NUM_THREADS; i++) 
	{
		printf("IN MAIN: Creating thread %d.\n", i);
		thread_args[i] = i;
		result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
		assert(!result_code);
  	}

  	printf("IN MAIN: All threads are created.\n");

	//wait for each thread to complete
	for (i = 0; i < NUM_THREADS; i++) 
	{
		result_code = pthread_join(threads[i], NULL);
		assert(!result_code);
		printf("IN MAIN: Thread %d has ended.\n", i);
	}

	printf("MAIN program has ended.\n");
	// copied code END
	
	return 0;
}

