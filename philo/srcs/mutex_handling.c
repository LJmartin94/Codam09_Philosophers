/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/01 19:46:44 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/14 23:29:51 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_create_all_mutexes(t_data *d)
{
	if (pthread_mutex_init(&(d->game_state), NULL))
		return (ft_mutex_init_failure(d));
	else
		d->game_state_init = 1;
	if (pthread_mutex_init(&(d->print_status), NULL))
		return (ft_mutex_init_failure(d));
	else
		d->print_status_init = 1;
	while (d->monitors_init < d->number_of_philosophers)
	{
		if (pthread_mutex_init(&(d->monitor_mutex[d->monitors_init]), NULL))
			return (ft_mutex_init_failure(d));
		else
			d->monitors_init++;
	}
	while (d->forks_initialised < d->number_of_philosophers)
	{
		if (pthread_mutex_init(&(d->forks[d->forks_initialised]), NULL))
			return (ft_mutex_init_failure(d));
		else
			d->forks_initialised++;
	}
	return (0);
}

int	ft_destroy_all_mutexes(t_data *d)
{
	if (d->game_state_init)
	{
		d->game_state_init = 0;
		if (pthread_mutex_destroy(&(d->game_state)))
			return (ft_mutex_destroy_failure(d));
	}
	if (d->print_status_init)
	{
		d->print_status_init = 0;
		if (pthread_mutex_destroy(&(d->print_status)))
			return (ft_mutex_destroy_failure(d));
	}
	while (d->monitors_init)
	{
		d->monitors_init--;
		if (pthread_mutex_destroy(&(d->monitor_mutex[d->monitors_init])))
			return (ft_mutex_destroy_failure(d));
	}
	while (d->forks_initialised)
	{
		d->forks_initialised--;
		if (pthread_mutex_destroy(&(d->forks[d->forks_initialised])))
			return (ft_mutex_destroy_failure(d));
	}
	return (0);
}

int	ft_mutex_init_failure(t_data *d)
{
	printf("A mutex failed to initialise correctly. Program will exit.\n");
	if (!ft_destroy_all_mutexes(d))
		ft_free_all(d);
	return (1);
}

int	ft_mutex_destroy_failure(t_data *d)
{
	printf("A mutex failed to be destroyed correctly. \
	Attempting to destroy other mutexes, then program will exit.\n");
	if (!ft_destroy_all_mutexes(d))
		ft_free_all(d);
	return (1);
}
