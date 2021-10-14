/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_thread.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 23:10:22 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/14 20:30:08 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_die(t_philo_thread_args *pta)
{
	pta->state = _ded;
	if (!pta->d->terminate)
		ft_print_status(pta->d, pta->state, pta->philo);
	pta->d->terminate = 1;
	return (0);
}

int	ft_sleep(t_philo_thread_args *pta)
{
	pta->state = _sleep;
	ft_drop_forks(pta->d, pta->philo, &(pta->forks_held));
	ft_print_status(pta->d, pta->state, pta->philo);
	return (0);
}

int	ft_think(t_philo_thread_args *pta)
{
	pta->state = _think;
	ft_print_status(pta->d, pta->state, pta->philo);
	return (0);
}

void	behavioural_loop(t_philo_thread_args *pta)
{
	if (ft_get_ms(pta->d) >= (pta->d->last_ate[pta->thread_id] + \
	pta->d->time_to_die))
		ft_die(pta);
	else if (ft_get_ms(pta->d) >= (pta->d->last_ate[pta->thread_id] + \
	pta->d->time_to_eat) && pta->state == _eat)
		ft_sleep(pta);
	else if (ft_get_ms(pta->d) >= (pta->d->last_ate[pta->thread_id] + \
	pta->d->time_to_eat + pta->d->time_to_sleep) && pta->state == _sleep)
		ft_think(pta);
	else if (pta->state == _think)
		ft_try_forks(pta);
}

void	*ft_philosophise(void *args)
{
	t_philo_thread_args	*pta;

	pta = (t_philo_thread_args *)args;
	pta->philo = pta->thread_id + 1;
	pta->state = _think;
	pta->d->last_ate[pta->thread_id] = 0;
	pta->d->full[pta->thread_id] = 0;
	pta->times_ate = 0;
	pta->forks_held = 0;
	while (!pta->d->clock_started)
		usleep(100);
	while (1 && !pta->d->terminate)
	{
		behavioural_loop(pta);
		usleep(100);
	}
	ft_drop_forks(pta->d, pta->philo, &(pta->forks_held));
	return (args);
}
