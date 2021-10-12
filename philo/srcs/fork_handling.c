/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 20:04:39 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/12 21:26:14 by limartin      ########   odam.nl         */
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

int	ft_stagger(t_data *d, int philo, int now)
{
	int	priority;
	int	wait_time;

	(void)now;
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

int	ft_try_forks(t_data *d, int philo, int now, int *forks_held)
{
	int	first_fork;
	int	second_fork;

	if (d->number_of_philosophers == 1)
		return (0);
	first_fork = (philo - (philo % 2)) % d->number_of_philosophers;
	second_fork = ((philo % 2) + (philo - 1)) % d->number_of_philosophers;
	usleep(ft_stagger(d, philo, now));
	*forks_held = 1;
	pthread_mutex_lock(&(d->forks[first_fork]));
	ft_print_status(d, _fork, philo);
	*forks_held = 2;
	pthread_mutex_lock(&(d->forks[second_fork]));
	ft_print_status(d, _fork, philo);
	ft_print_status(d, _eat, philo);
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
