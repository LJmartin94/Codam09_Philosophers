/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 21:32:55 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/04 01:33:29 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	c_kill_all_threads(t_data *d)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(d->game_state));
	d->p_terminate = 1;
	pthread_mutex_unlock(&(d->game_state));
	pthread_join(d->monitor, NULL);
	while (i < d->number_of_philosophers)
	{
		pthread_join(d->philosophers[i], NULL);
		i++;
	}
	return (0);
}

int	ft_thread_creation_error(t_data *d)
{
	printf("Thread creation error: \n"
		"A call to pthread_create failed to complete succesfully.\n"
		"Program will exit.\n");
	if (!ft_destroy_all_mutexes(d))
		ft_free_all(d);
	return (1);
}

int	p_partial_thread_killer(int status, t_data *d)
{
	int	i;

	i = 0;
	d->p_terminate = 1;
	pthread_mutex_unlock(&(d->game_state));
	if (status == -1)
		status = d->number_of_philosophers;
	while (i < status)
	{
		pthread_join(d->philosophers[i], NULL);
		i++;
	}
	ft_thread_creation_error(d);
	return (1);
}

int	c_create_threads(t_data *d)
{
	int		this_thread;

	this_thread = 0;
	pthread_mutex_lock(&(d->game_state));
	while (this_thread < d->number_of_philosophers)
	{
		(d->args[this_thread]).d = d;
		(d->args[this_thread]).thread_id = this_thread;
		if (pthread_create(&(d->philosophers[this_thread]), NULL, \
		c_philosophise, &((d->args)[this_thread])))
			return (p_partial_thread_killer(this_thread, d));
		this_thread++;
	}
	if (pthread_create(&(d->monitor), NULL, c_monitor_philos, (void *)(d)))
		return (p_partial_thread_killer(-1, d));
	ft_start_clock(d);
	pthread_mutex_unlock(&(d->game_state));
	return (0);
}
