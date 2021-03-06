/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_thread.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 23:10:22 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/21 16:06:52 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	c_dead(t_philo_thread_args *pta)
{
	pta->state = _ded;
	cp_request_print(pta->d, pta->state, pta->philo, 'c');
	return (0);
}

int	c_sleep(t_philo_thread_args *pta)
{
	int	go_ret;

	pta->state = _sleep;
	pta->state_time = ft_get_ms(pta->d);
	ft_drop_forks(pta->d, pta->philo, &(pta->forks_held));
	go_ret = cp_request_print(pta->d, pta->state, pta->philo, 'c');
	return (go_ret);
}

int	c_think(t_philo_thread_args *pta)
{
	int	go_ret;

	pta->state = _think;
	pta->state_time = ft_get_ms(pta->d);
	go_ret = cp_request_print(pta->d, pta->state, pta->philo, 'c');
	return (go_ret);
}

void	c_behavioural_loop(t_philo_thread_args *pta, int *last_ate, int *go)
{
	int	now;

	now = ft_get_ms(pta->d);
	if (now > (*last_ate + pta->d->time_to_die))
		*go = c_dead(pta);
	if (now >= (*last_ate + pta->d->time_to_eat) && pta->state == _eat)
		*go = c_sleep(pta);
	else if (now >= (*last_ate + pta->d->time_to_eat + pta->d->time_to_sleep) \
	&& pta->state == _sleep)
		*go = c_think(pta);
	if (pta->state == _think)
		*go = c_try_forks(pta, last_ate);
}

void	*c_philosophise(void *args)
{
	t_philo_thread_args	*pta;
	int					local_last_ate;
	int					go;

	pta = (t_philo_thread_args *)args;
	pta->philo = pta->thread_id + 1;
	pta->state = _think;
	local_last_ate = 0;
	pta->first_fork = (pta->philo - (pta->philo % 2)) % \
	pta->d->number_of_philosophers;
	pta->second_fork = ((pta->philo % 2) + (pta->philo - 1)) % \
	pta->d->number_of_philosophers;
	go = cp_continue(pta->d, 'c');
	while (go)
	{
		c_behavioural_loop(pta, &local_last_ate, &go);
		accusleep(pta->d, 500);
		if (pta->d->notepme > 0 && pta->times_ate >= pta->d->notepme)
			go = cp_continue(pta->d, 'c');
	}
	ft_drop_forks(pta->d, pta->philo, &(pta->forks_held));
	return (args);
}
