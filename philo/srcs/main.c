/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:13:22 by lindsay       #+#    #+#                 */
/*   Updated: 2021/09/30 18:38:00 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philosophise(void *args)
{
	t_data	*d;
	int		philosopher;
	t_state	state;
	int		last_ate;
	int		now;
	
	d = ((t_philo_thread_args *)args)->d;
	philosopher = ((t_philo_thread_args *)args)->thread_id + 1;
	// FREE ARG MALLOC HERE, SET TO NULL
	state = _think;
	last_ate = 0;
	while (1 && !d->terminate)
	{
		now = ft_get_ms(d);
		if (now >= (last_ate + d->time_to_die))
		{
			pthread_mutex_lock(&(d->game_state));
			state = _ded;
			if (!d->terminate)
				ft_print_status(d, state, philosopher);
			d->terminate = 1;
			pthread_mutex_unlock(&(d->game_state));
		}
		else if (now >= (last_ate + d->time_to_eat) && state == _eat)
		{
			state = _sleep;
			ft_print_status(d, state, philosopher);
			//DROP FORKS
		}
		else if (now >= (last_ate + d->time_to_eat + d->time_to_sleep) && state == _sleep)
		{
			state = _think;
			ft_print_status(d, state, philosopher);
		}
		else if (state == _think)
		{
			state = _fork;
			ft_print_status(d, state, philosopher);
		}
		else if (state == _fork)
		{
			//grab second fork, or drop first
			ft_print_status(d, state, philosopher);
			state = _eat;
			ft_print_status(d, state, philosopher);
			last_ate = now;
		}
		usleep(100);
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
	ft_malloc_all(&d);
	ft_create_all_mutexes(&d);
	ft_start_clock(&d);
	this_thread = 0;
	while (this_thread < d.number_of_philosophers)
	{
		(d.args[this_thread]).thread_id = this_thread;
		(d.args[this_thread]).d = &d;
		printf("IN MAIN: Creating thread %d.\n", this_thread);
		pthread_create(&(d.philosophers[this_thread]), NULL, \
		ft_philosophise, &((d.args)[this_thread]));
		usleep(100);
		this_thread++;
	}
	printf("IN MAIN: All threads are created.\n");
	while(!d.terminate)
	{
		usleep(100);
	}
	ft_kill_all_threads(&d);
	ft_destroy_all_mutexes(&d);
	if (printf("MAIN program has ended.\n"))
		return (0);
	else
		return (0);
}
