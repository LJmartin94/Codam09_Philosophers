/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_threads.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 21:32:55 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/15 00:35:55 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_create_threads(t_data *d)
{
	int		this_thread;

	this_thread = 0;
	pthread_mutex_lock(&(d->game_state));
	while (this_thread < d->number_of_philosophers)
	{
		(d->args[this_thread]).thread_id = this_thread;
		(d->args[this_thread]).d = d;
		pthread_create(&(d->philosophers[this_thread]), NULL, \
		ft_philosophise, &((d->args)[this_thread])); // Need to protect thread create too
		this_thread++;
	}
	ft_start_clock(d);
	pthread_mutex_unlock(&(d->game_state));
	pthread_create(&(d->monitor), NULL, monitor_philos, (void *)(d));
	return (0);
}
