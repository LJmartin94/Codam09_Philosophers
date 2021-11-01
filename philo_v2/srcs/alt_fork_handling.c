/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alt_fork_handling.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 20:04:39 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/01 19:43:01 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	wait_your_turn(int now, int group, t_data *d)
{
	int	test_time;
	int	groups;
	int	a_second_eat;

	groups = (d->number_of_philosophers % 2) + 2;
	a_second_eat = d->time_to_eat * groups;
	if ((d->time_to_sleep + d->time_to_eat) > a_second_eat)
		a_second_eat = d->time_to_sleep + d->time_to_eat;
	test_time = now % a_second_eat;
	if (group == 0 && test_time >= 0 && test_time < d->time_to_eat)
		return (0);
	else if (group == 1 && test_time >= d->time_to_eat && \
	test_time < (d->time_to_eat * 2))
		return (0);
	else if (group == 2 && test_time >= (d->time_to_eat * 2) && \
	test_time < (d->time_to_eat * 3))
		return (0);
	else
		return (1);
}

int	ft_stagger(t_data *d, int philo)
{
	int	now;
	int	group;

	now = ft_get_ms(d);
	group = philo % ((d->number_of_philosophers % 2) + 2);
	while (wait_your_turn(now, group, d))
	{
		now = ft_get_ms(d);
		usleep(100);
	}
	return (0);
}

/*
** Odd-numbers try left fork first, Even-numbers try right fork first.
*/

int	ft_try_forks(t_philo_thread_args *pta, int *last_ate)
{
	int	first_fork;
	int	second_fork;

	if (pta->d->number_of_philosophers == 1)
		return (0);
	first_fork = (pta->philo - (pta->philo % 2)) % \
	pta->d->number_of_philosophers;
	second_fork = ((pta->philo % 2) + (pta->philo - 1)) % \
	pta->d->number_of_philosophers;
	ft_stagger(pta->d, pta->philo);
	pta->forks_held = 1;
	pthread_mutex_lock(&(pta->d->forks[first_fork]));
	ft_request_print(pta->d, _fork, pta->philo, 0);
	pta->forks_held = 2;
	pthread_mutex_lock(&(pta->d->forks[second_fork]));
	ft_request_print(pta->d, _eat, pta->philo, 0);
	pta->state = _eat;
	pta->times_ate = pta->times_ate + 1;
	pthread_mutex_lock(&(pta->d->game_state));
	*last_ate = ft_get_ms(pta->d);
	pta->d->last_ate[pta->thread_id] = *last_ate;
	if (pta->d->notepme > 0 && pta->times_ate >= pta->d->notepme)
		pta->d->full[pta->thread_id] = 1;
	pthread_mutex_unlock(&(pta->d->game_state));
	return (1);
}

int	ft_drop_forks(t_data *d, int philo, int *forks_held)
{
	int	first_fork;
	int	second_fork;

	if (d->number_of_philosophers == 1 || *forks_held == 0)
		return (0);
	first_fork = (philo - (philo % 2)) % d->number_of_philosophers;
	second_fork = ((philo % 2) + (philo - 1)) % d->number_of_philosophers;
	if (*forks_held == 2)
		pthread_mutex_unlock(&(d->forks[second_fork]));
	pthread_mutex_unlock(&(d->forks[first_fork]));
	*forks_held = 0;
	return (1);
}
