/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 17:28:13 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/01 15:56:08 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Guarantees all data in the data struct initially set to NULL
int	ft_data_null(t_data *d)
{
	d->number_of_philosophers = -1;
	d->time_to_die = -1;
	d->time_to_eat = -1;
	d->time_to_sleep = -1;
	d->number_of_times_each_philosopher_must_eat = -1;
	d->allocation_failure = 0;
	d->game_state_init = 0;
	d->print_status_init = 0;
	d->forks_initialised = 0;
	d->philosophers = NULL;
	d->args = NULL;
	d->forks = NULL;
	d->terminate = 0;
	return (0);
}

int	ft_malloc_all(t_data *d)
{
	d->philosophers = (pthread_t *) \
	malloc(sizeof(pthread_t) * d->number_of_philosophers);
	d->args = (t_philo_thread_args *) \
	malloc(sizeof(t_philo_thread_args) * d->number_of_philosophers);
	d->forks = (pthread_mutex_t *) \
	malloc(sizeof(pthread_mutex_t) * d->number_of_philosophers);
	if (!d->philosophers || !d->args || !d->forks)
		d->allocation_failure = 1;
	return (0);
}

int	ft_free_all(t_data *d)
{
	//TO DO: Free everything, and also tidy up malloc fails.
	(void) d;
	return (0);
}

int	ft_create_all_mutexes(t_data *d)
{
	if (pthread_mutex_init(&(d->game_state), NULL))
	{
		perror("errno on mutex init: ");
		return (errno); // NEED PROPER ERROR MESSAGE HERE
	}
	else
		d->game_state_init = 1;
	if (pthread_mutex_init(&(d->print_status), NULL))
	{
		perror("errno on mutex init: ");
		return (errno); // NEED PROPER ERROR MESSAGE HERE
	}
	else
		d->print_status_init = 1;
	while (d->forks_initialised < d->number_of_philosophers)
	{
		if (pthread_mutex_init(&(d->forks[d->forks_initialised]), NULL))
		{
			perror("errno on mutex init: ");
			return (errno); // NEED PROPER ERROR MESSAGE HERE
		}
		d->forks_initialised++;
	}
	return (0);
}

int	ft_destroy_all_mutexes(t_data *d)
{
	if (d->game_state_init)
	{
		if (pthread_mutex_destroy(&(d->game_state)))
		{
			perror("errno on mutex destroy: ");
			return (errno); // NEED PROPER ERROR MESSAGE HERE
		}
	}
	if (d->print_status_init)
	{
		if (pthread_mutex_destroy(&(d->print_status)))
		{
			perror("errno on mutex destroy: ");
			return (errno); // NEED PROPER ERROR MESSAGE HERE
		}
	}
	return (0);
}
