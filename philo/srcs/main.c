/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:13:22 by lindsay       #+#    #+#                 */
/*   Updated: 2021/10/07 14:09:21 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_ded(t_data	*d, int last_ate)
{
	if (ft_get_ms(d) >= (last_ate + d->time_to_die))
		return (1);
	else
		return (0);
}

void	*ft_philosophise(void *args)
{
	t_data	*d;
	int		philo;
	t_state	state;

	d = ((t_philo_thread_args *)args)->d;
	philo = ((t_philo_thread_args *)args)->thread_id + 1;
	state = _think;
	pthread_mutex_lock(&(d->mutex_last_ate));
	d->last_ate[philo - 1] = 0;
	pthread_mutex_unlock(&(d->mutex_last_ate));
	while (1 && !d->terminate)
	{
		if (ft_get_ms(d) >= (d->last_ate[philo - 1] + d->time_to_die))
		{
			state = _ded;
			if (!d->terminate)
				ft_print_status(d, state, philo);
			d->terminate = 1;
		}
		else if (ft_get_ms(d) >= (d->last_ate[philo - 1] + d->time_to_eat) \
		&& state == _eat)
		{
			state = _sleep;
			ft_drop_forks(d, philo);
			ft_print_status(d, state, philo);
		}
		else if (ft_get_ms(d) >= (d->last_ate[philo - 1] + d->time_to_eat + \
		d->time_to_sleep) && state == _sleep)
		{
			state = _think;
			ft_print_status(d, state, philo);
		}
		else if (state == _think)
		{
			if (ft_try_forks(d, philo, ft_get_ms(d)))
			{
				state = _eat;
				pthread_mutex_lock(&(d->mutex_last_ate));
				d->last_ate[philo - 1] = ft_get_ms(d);
				pthread_mutex_unlock(&(d->mutex_last_ate));
			}
		}
		usleep(100);
	}
	return (args);
}

// THERE ARE TWO PROBLEMS WITH THE CODE RIGHT NOW THAT I AM AWARE OF: 
// PHILOS EAT AFTER THEY SHOULD DIE - E.G. 3 2001 1000 1000, PHILO 2 EATS AT 0 & 3000 AND NOT IN BETWEEN.
// PHILOS DIE, AND LOCK UP THE PROGRAM DUE TO UNRELEASED MUTEXES - E.G. 3 999 1000 1000.

int	main(int argc, char **argv)
{
	t_data	d;
	int		this_thread;

	ft_data_null(&d);
	if (ft_error_checker(argc, argv, &d))
		return (1);
	if (ft_malloc_all(&d))
		return (ft_malloc_failure(&d));
	if (ft_create_all_mutexes(&d))
		return (1);
	ft_start_clock(&d); //only do this after all threads are created. Start running threads once clock is started.
	this_thread = 0;
	while (this_thread < d.number_of_philosophers)
	{
		(d.args[this_thread]).thread_id = this_thread;
		(d.args[this_thread]).d = &d;
		printf("IN MAIN: Creating thread %d.\n", this_thread);
		pthread_create(&(d.philosophers[this_thread]), NULL, \
		ft_philosophise, &((d.args)[this_thread]));
		this_thread++;
	}
	printf("IN MAIN: All threads are created at %d.\n", ft_get_ms(&d));
	while (!d.terminate)
	{
		usleep(100);
	}
	ft_kill_all_threads(&d);
	ft_destroy_all_mutexes(&d);
	ft_free_all(&d);
	if (printf("MAIN program has ended at %d.\n", ft_get_ms(&d)))
		return (0);
	else
		return (0);
}
