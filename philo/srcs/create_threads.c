/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_threads.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 21:32:55 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/12 22:23:12 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_create_threads(t_data *d)
{
	int		this_thread;

	this_thread = 0;
	while (this_thread < d->number_of_philosophers)
	{
		(d->args[this_thread]).thread_id = this_thread;
		(d->args[this_thread]).d = d;
		pthread_create(&(d->philosophers[this_thread]), NULL, \
		ft_philosophise, &((d->args)[this_thread])); // Need to protect thread create too
		this_thread++;
	}
	ft_start_clock(d);
	pthread_create(&(d->monitor), NULL, monitor_philos, (void *)(d));
	return (0);
}
