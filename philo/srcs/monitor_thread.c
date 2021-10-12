/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 13:42:13 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/12 16:53:57 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_philos(void *args)
{
	int i;
	int now;
	t_data *d;

	d = (t_data *)args;
	while (!d->clock_started)
		usleep(100);
	while (!d->terminate)
	{
		i = 0;
		now = ft_get_ms(d);
		
		while (i < d->number_of_philosophers && !d->terminate)
		{
			if (now >= d->last_ate[i] + d->time_to_die && now > 0)
				ft_print_status(d, _ded, (i+1));
			else
				i++;
		}
		usleep(100);
	}	
	return ((void *)0);
}