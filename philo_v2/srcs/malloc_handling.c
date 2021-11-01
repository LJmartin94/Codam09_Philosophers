/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/01 19:44:47 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/15 01:15:29 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_malloc_all(t_data *d)
{
	d->philosophers = (pthread_t *) \
	malloc(sizeof(pthread_t) * d->number_of_philosophers);
	d->args = (t_philo_thread_args *) \
	malloc(sizeof(t_philo_thread_args) * d->number_of_philosophers);
	d->forks = (pthread_mutex_t *) \
	malloc(sizeof(pthread_mutex_t) * d->number_of_philosophers);
	d->monitor_mutex = (pthread_mutex_t *) \
	malloc(sizeof(pthread_mutex_t) * d->number_of_philosophers);
	d->last_ate = (int *) \
	malloc(sizeof(int) * d->number_of_philosophers);
	d->full = (int *) \
	malloc(sizeof(int) * d->number_of_philosophers);
	d->game_over = (int *) \
	malloc(sizeof(int) * d->number_of_philosophers);
	if (!d->philosophers || !d->args || !d->forks || !d->last_ate \
	|| !d->full || !d->monitor_mutex || !d->game_over)
		return (1);
	return (0);
}

int	ft_free_all(t_data *d)
{
	if (d->philosophers)
		free(d->philosophers);
	d->philosophers = NULL;
	if (d->args)
		free(d->args);
	d->args = NULL;
	if (d->forks)
		free(d->forks);
	d->forks = NULL;
	if (d->monitor_mutex)
		free(d->monitor_mutex);
	d->monitor_mutex = NULL;
	if (d->last_ate)
		free(d->last_ate);
	d->last_ate = NULL;
	if (d->full)
		free(d->full);
	d->full = NULL;
	if (d->game_over)
		free(d->game_over);
	d->game_over = NULL;
	return (0);
}

int	ft_malloc_failure(t_data *d)
{
	ft_free_all(d);
	printf("Memory allocation error: \n\
	A malloc call failed to complete succesfully.\n\
	Program will exit.\n");
	return (1);
}
