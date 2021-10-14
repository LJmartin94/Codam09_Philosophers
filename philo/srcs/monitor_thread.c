/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 13:42:13 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/15 00:37:18 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_philos(void *args)
{
	int		i;
	int		now;
	int		full_phils;
	t_data	*d;

	d = (t_data *)args;
	pthread_mutex_lock(&(d->game_state));
	pthread_mutex_unlock(&(d->game_state));
	while (!d->terminate)
	{
		i = 0;
		full_phils = 0;
		now = ft_get_ms(d);
		while (i < d->number_of_philosophers && !d->terminate)
		{
			//monitor mutex lock
			pthread_mutex_lock(&(d->monitor_mutex[i]));
			if (now >= d->last_ate[i] + d->time_to_die && now > 0)
				ft_print_status(d, _ded, (i + 1));
			if (d->notepme > 0 && d->full[i] == 1)
				full_phils++;
			pthread_mutex_unlock(&(d->monitor_mutex[i]));
			//monitor mutex unlock
			i++;
		}
		if (d->notepme > 0 && full_phils >= d->number_of_philosophers)
			d->terminate = 1;
	}
	return ((void *)0);
}
