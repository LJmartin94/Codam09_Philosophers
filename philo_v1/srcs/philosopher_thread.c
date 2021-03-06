/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_thread.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 23:10:22 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/23 18:00:37 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	int	local_last_ate;
	int	now;

	pthread_mutex_lock(&(pta->d->monitor_mutex[pta->thread_id]));
	local_last_ate = pta->d->last_ate[pta->thread_id];
	pthread_mutex_unlock(&(pta->d->monitor_mutex[pta->thread_id]));
	now = ft_get_ms(pta->d);
	if (now >= (local_last_ate + \
	pta->d->time_to_eat) && pta->state == _eat)
		ft_sleep(pta);
	else if (now >= (local_last_ate + \
	pta->d->time_to_eat + pta->d->time_to_sleep) && pta->state == _sleep)
		ft_think(pta);
	if (pta->state == _think)
		ft_try_forks(pta);
}

void	*ft_philosophise(void *args)
{
	t_philo_thread_args	*pta;

	pta = (t_philo_thread_args *)args;
	pta->philo = pta->thread_id + 1;
	pta->state = _think;
	pthread_mutex_lock(&(pta->d->monitor_mutex[pta->thread_id]));
	pta->d->last_ate[pta->thread_id] = 0;
	pta->d->full[pta->thread_id] = 0;
	pthread_mutex_unlock(&(pta->d->monitor_mutex[pta->thread_id]));
	pta->times_ate = 0;
	pta->forks_held = 0;
	pthread_mutex_lock(&(pta->d->game_state));
	pthread_mutex_unlock(&(pta->d->game_state));
	while (ft_continue(pta->d, pta->thread_id))
	{
		behavioural_loop(pta);
		usleep(100 + (pta->d->number_of_philosophers * 3 / 4));
	}
	ft_drop_forks(pta->d, pta->philo, &(pta->forks_held));
	return (args);
}
