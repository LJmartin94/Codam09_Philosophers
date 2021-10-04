/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grab_forks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 20:04:39 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/04 22:52:13 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
	int priority;
	int wait_time;

	wait_time = 100;
	if (philo % 2 == 0)
		priority = 1;
	else if (!(d->number_of_philosophers % 2) ||\
	 philo != d->number_of_philosophers)
		priority = 2;
	else
		priority = 3;
	if (now <= d->time_to_eat)
		return (wait_time * (priority - 1))
	return (0);
}

/*
** Odd-numbers try left fork first, Even-numbers try right fork first.
*/

int ft_try_forks(t_data *d, int philo, int now)
{
	int first_fork;
	int second_fork;

	if (d->number_of_philosophers == 1)
		return (0);
	first_fork = (philo - (philo % 2)) % d->number_of_philosophers;
	second_fork = ((philo % 2) + (philo - 1)) % d->number_of_philosophers;
	if (now <= d->time_to_eat)
		usleep(ft_stagger);
	
	
}

