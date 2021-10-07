/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   killthreads.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 17:19:52 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/07 15:17:10 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_kill_all_threads(t_data *d)
{
	int	i;

	i = 0;
	d->terminate = 1;
	pthread_join(d->monitor, NULL);
	while (i < d->number_of_philosophers)
	{
		pthread_join(d->philosophers[i], NULL);
		i++;
	}
	return (0);
}
