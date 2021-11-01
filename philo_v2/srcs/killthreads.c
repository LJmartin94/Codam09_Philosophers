/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   killthreads.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 17:19:52 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/01 19:06:02 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_kill_all_threads(t_data *d)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(d->game_state));
	ft_game_over(d, -1);
	pthread_mutex_unlock(&(d->game_state));
	pthread_join(d->monitor, NULL);
	while (i < d->number_of_philosophers)
	{
		pthread_join(d->philosophers[i], NULL);
		i++;
	}
	return (0);
}
