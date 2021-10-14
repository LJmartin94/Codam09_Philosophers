/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 20:04:39 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/14 20:52:19 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** If philosophers haven't eaten at all yet, 
** this function staggers their starting times.
** Even-numbered philosophers start (priority group 1) 
** Odd-numbered philosophers go second (priority group 2)
**
** If the total number of philosophers is also odd (e.g. 3), then the 
** first and the last philosopher can't eat at the same time as they 
** share a fork.
** In this case, the last philo eats the very last (priority group 3).
*/

int	ft_stagger(t_data *d, int philo)
{
	int	priority;
	int	wait_time;

	wait_time = 250;
	if (philo % 2 == 0)
		priority = 1;
	else if (!(d->number_of_philosophers % 2) || \
	philo != d->number_of_philosophers)
		priority = 2;
	else
		priority = 3;
	return (wait_time * (priority - 1));
}

/*
** Odd-numbers try left fork first, Even-numbers try right fork first.
*/

int	ft_try_forks(t_philo_thread_args *pta)
{
	int	first_fork;
	int	second_fork;

	if (pta->d->number_of_philosophers == 1)
		return (0);
	first_fork = (pta->philo - (pta->philo % 2)) % pta->d->number_of_philosophers;
	second_fork = ((pta->philo % 2) + (pta->philo - 1)) % pta->d->number_of_philosophers;
	usleep(ft_stagger(pta->d, pta->philo));
	pta->forks_held = 1;
	pthread_mutex_lock(&(pta->d->forks[first_fork]));
	ft_print_status(pta->d, _fork, pta->philo);
	pta->forks_held = 2;
	pthread_mutex_lock(&(pta->d->forks[second_fork]));
	ft_print_status(pta->d, _fork, pta->philo);
	ft_print_status(pta->d, _eat, pta->philo);
	pta->state = _eat;
	pta->times_ate = pta->times_ate + 1;
	pta->d->last_ate[pta->thread_id] = ft_get_ms(pta->d);
	if (pta->d->notepme > 0 && pta->times_ate >= pta->d->notepme)
		pta->d->full[pta->thread_id] = 1;
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
