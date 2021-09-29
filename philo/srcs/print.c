/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 17:42:59 by limartin      #+#    #+#                 */
/*   Updated: 2021/09/29 17:25:39 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_print_status(t_data *d, t_print_reason reason, int philo_id)
{
	int 	ms;
	
	pthread_mutex_lock(&(d->print_status));
	ms = ft_get_ms(d);
	if (reason == _fork)
		printf("%d Philosopher %d has taken a fork\n", ms, philo_id);
	else if (reason == _eat)
		printf("%d Philosopher %d is eating\n", ms, philo_id);
	else if (reason == _sleep)
		printf("%d Philosopher %d is sleeping\n", ms, philo_id);
	else if (reason == _think)
		printf("%d Philosopher %d is thinking\n", ms, philo_id);
	else if (reason == _ded)
		printf("%d Philosopher %d died\n", ms, philo_id);
	pthread_mutex_unlock(&(d->print_status));
	return (0);
}
