/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 13:42:13 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/07 15:22:38 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_ded(t_data	*d, int last_ate)
{
	if (ft_get_ms(d) >= (last_ate + d->time_to_die))
		return (1);
	else
		return (0);
}

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
			if (now >= d->last_ate[i] + d->time_to_die)
				ft_print_status(d, _ded, (i+1));
			else
				i++;
		}
	}	
	return ((void *)0);
}