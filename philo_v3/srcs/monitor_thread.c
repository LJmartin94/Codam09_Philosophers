/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 13:42:13 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/03 15:54:54 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	ft_continue(t_data *d, int index)
// {
// 	int	ret;

// 	(void)index;  //TODO: remove
// 	pthread_mutex_lock(&(d->game_state));
// 	ret = !(d->terminate);
// 	pthread_mutex_unlock(&(d->game_state));
// 	return (ret);
// }

// int	p_game_over(t_data *d)
// {
// 	int	i;

// 	i = 0;
// 	d->terminate = 1;
// 	return (0);
// }

// int	check_philo(int *i, int now, int *full_phils, t_data *d)
// {
// 	if (now >= d->last_ate[*i] + d->time_to_die && now > 0)
// 		ft_print_status(d, _ded, (*i + 1), 1);
// 	if (d->notepme > 0 && d->full[*i] == 1)
// 		(*full_phils)++;
// 	(*i)++;
// 	return (0);
// }

void	*monitor_philos(void *args)
{
	(void)args;
// 	int		i;
// 	int		now;
// 	int		full_phils;
// 	t_data	*d;

// 	d = (t_data *)args;
// 	while (ft_continue(d, -1))
// 	{
// 		pthread_mutex_lock(&(d->game_state)); // THESE MUTEXES CAUSE THE DEADLOCK
// 		i = 0;
// 		full_phils = 0;
// 		now = ft_get_ms(d);
// 		while (i < d->number_of_philosophers)
// 		{
// 			check_philo(&i, now, &full_phils, d);
// 		}
// 		if (d->notepme > 0 && full_phils >= d->number_of_philosophers)
// 			ft_game_over(d, -1);
// 		pthread_mutex_unlock(&(d->game_state)); // THESE MUTEXES CAUSE THE DEADLOCK
// 		usleep(100);
// 	}
	return ((void *)0);
}
