/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:13:22 by lindsay       #+#    #+#                 */
/*   Updated: 2021/10/12 21:55:23 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	behavioural_loop(t_data	*d, int philo, t_state *state, int *forks_held)
{
	if (ft_get_ms(d) >= (d->last_ate[philo - 1] + d->time_to_die))
	{
		*state = _ded;
		if (!d->terminate)
			ft_print_status(d, *state, philo);
		d->terminate = 1;
	}
	else if (ft_get_ms(d) >= (d->last_ate[philo - 1] + d->time_to_eat) \
	&& *state == _eat)
	{
		*state = _sleep;
		ft_drop_forks(d, philo, forks_held);
		ft_print_status(d, *state, philo);
	}
	else if (ft_get_ms(d) >= (d->last_ate[philo - 1] + d->time_to_eat + \
	d->time_to_sleep) && *state == _sleep)
	{
		*state = _think;
		ft_print_status(d, *state, philo);
	}
	else if (*state == _think)
	{
		if (ft_try_forks(d, philo, ft_get_ms(d), forks_held))
		{
			*state = _eat;
			d->last_ate[philo - 1] = ft_get_ms(d);
		}
	}
}

void	*ft_philosophise(void *args)
{
	t_data	*d;
	int		philo;
	t_state	state;
	int		forks_held;

	d = ((t_philo_thread_args *)args)->d;
	philo = ((t_philo_thread_args *)args)->thread_id + 1;
	state = _think;
	d->last_ate[philo - 1] = 0;
	while (!d->clock_started)
		usleep(100);
	while (1 && !d->terminate)
	{
		behavioural_loop(d, philo, &state, &forks_held);
		usleep(100);
	}
	ft_drop_forks(d, philo, &forks_held);
	return (args);
}

int	main(int argc, char **argv)
{
	t_data	d;

	ft_data_null(&d);
	if (ft_error_checker(argc, argv, &d))
		return (1);
	if (ft_malloc_all(&d))
		return (ft_malloc_failure(&d));
	if (ft_create_all_mutexes(&d))
		return (1);
	ft_create_threads(&d);
	while (!d.terminate)
		usleep(100);
	ft_kill_all_threads(&d);
	ft_destroy_all_mutexes(&d);
	ft_free_all(&d);
	return (0);
}
