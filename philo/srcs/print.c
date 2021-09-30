/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 17:42:59 by limartin      #+#    #+#                 */
/*   Updated: 2021/09/30 20:59:34 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_print_status(t_data *d, t_state reason, int philo_id)
{
	int 	ms;
	
	pthread_mutex_lock(&(d->print_status));
	if (!d->terminate)
	{
		ms = ft_get_ms(d);
		if (reason == _ded)
		{
			printf(COLOUR_RED "%d Philosopher %d died\n" COLOUR_DEFAULT, ms, philo_id);
			d->terminate = 1;
		}
		else if (reason == _fork)
			printf(COLOUR_YELLOW "%d Philosopher %d has taken a fork\n" COLOUR_DEFAULT, ms, philo_id);
		else if (reason == _eat)
			printf(COLOUR_GREEN "%d Philosopher %d is eating\n" COLOUR_DEFAULT, ms, philo_id);
		else if (reason == _sleep)
			printf(COLOUR_BLUE "%d Philosopher %d is sleeping\n" COLOUR_DEFAULT, ms, philo_id);
		else if (reason == _think)
			printf(COLOUR_CYAN "%d Philosopher %d is thinking\n" COLOUR_DEFAULT, ms, philo_id);
	}
	pthread_mutex_unlock(&(d->print_status));
	return (0);
}
