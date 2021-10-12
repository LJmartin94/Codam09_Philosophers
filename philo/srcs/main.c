/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:13:22 by lindsay       #+#    #+#                 */
/*   Updated: 2021/10/12 19:16:46 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philosophise(void *args)
{
	t_data	*d;
	int		philo;
	t_state	state;
	int		forks_held;

	d = ((t_philo_thread_args *)args)->d;
	philo = ((t_philo_thread_args *)args)->thread_id + 1;
	state = _think;
	// pthread_mutex_lock(&(d->mutex_last_ate));
	d->last_ate[philo - 1] = 0;
	// pthread_mutex_unlock(&(d->mutex_last_ate));
	while (!d->clock_started)
		usleep(100);
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
			ft_drop_forks(d, philo, &forks_held);
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
			if (ft_try_forks(d, philo, ft_get_ms(d), &forks_held))
			{
				state = _eat;
				// pthread_mutex_lock(&(d->mutex_last_ate));
				d->last_ate[philo - 1] = ft_get_ms(d);
				// pthread_mutex_unlock(&(d->mutex_last_ate));
			}
		}
		usleep(100);
		if (d->terminate)
			ft_drop_forks(d, philo, &forks_held);
	}
	return (args);
}

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
	this_thread = 0;
	while (this_thread < d.number_of_philosophers)
	{
		(d.args[this_thread]).thread_id = this_thread;
		(d.args[this_thread]).d = &d;
		printf("IN MAIN: Creating thread %d.\n", this_thread);
		pthread_create(&(d.philosophers[this_thread]), NULL, \
		ft_philosophise, &((d.args)[this_thread])); // Need to protect thread create too
		this_thread++;
	}
	ft_start_clock(&d);
	pthread_create(&d.monitor, NULL, monitor_philos, (void *)(&d));
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
