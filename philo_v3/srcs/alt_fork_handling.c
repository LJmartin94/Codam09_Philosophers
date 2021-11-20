/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alt_fork_handling.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 20:04:39 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/20 09:16:05 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	wait_your_turn(int now, int group, t_data *d, int state_time)
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

int	ft_stagger(t_data *d, int philo, int state_time)
{
	int	now;
	int	group;

	now = ft_get_ms(d);
	group = philo % ((d->number_of_philosophers % 2) + 2);
	while (wait_your_turn(now, group, d, state_time))
	{
		now = ft_get_ms(d);
		accusleep(d, 250);
	}
	return (0);
}

/*
** Odd-numbers try left fork first, Even-numbers try right fork first.
*/

int	c_try_forks(t_philo_thread_args *pta, int *last_ate)
{
	int	go_ret;

	if (pta->d->number_of_philosophers == 1)
		return (1);
	ft_stagger(pta->d, pta->philo, pta->state_time);
	pta->forks_held = 1;
	pthread_mutex_lock(&(pta->d->forks[pta->first_fork]));
	go_ret = cp_request_print(pta->d, _fork, pta->philo, 'c');
	pta->forks_held = 2;
	pthread_mutex_lock(&(pta->d->forks[pta->second_fork]));
	go_ret = cp_request_print(pta->d, _eat, pta->philo, 'c');
	*last_ate = ft_get_ms(pta->d);
	pta->state_time = *last_ate;
	pta->state = _eat;
	pta->times_ate = pta->times_ate + 1;
	pthread_mutex_lock(&(pta->d->game_state));
	pta->d->p_last_ate[pta->thread_id] = *last_ate;
	if (pta->d->notepme > 0 && pta->times_ate >= pta->d->notepme)
		pta->d->p_full[pta->thread_id] = 1;
	go_ret = cp_continue(pta->d, 'p');
	pthread_mutex_unlock(&(pta->d->game_state));
	return (go_ret);
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
