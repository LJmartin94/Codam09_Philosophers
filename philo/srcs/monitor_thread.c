/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 13:42:13 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/14 20:55:32 by limartin      ########   odam.nl         */
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
	while (!d->clock_started)
		usleep(100);
	while (!d->terminate)
	{
		i = 0;
		full_phils = 0;
		now = ft_get_ms(d);
		while (i < d->number_of_philosophers && !d->terminate)
		{
			if (now >= d->last_ate[i] + d->time_to_die && now > 0)
				ft_print_status(d, _ded, (i + 1));
			if (d->notepme > 0 && d->full[i] == 1)
				full_phils++;
			i++;
		}
		if (d->notepme > 0 && full_phils >= d->number_of_philosophers)
			d->terminate = 1;
	}
	return ((void *)0);
}
