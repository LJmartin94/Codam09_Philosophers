/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 13:42:13 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/28 22:20:10 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_continue(t_data *d, int index)
{
	int	ret;

	if (index == -1)
	{
		pthread_mutex_lock(&(d->game_state));
		ret = !(d->terminate);
		pthread_mutex_unlock(&(d->game_state));
	}
	else
	{
		pthread_mutex_lock(&(d->monitor_mutex[index]));
		ret = !(d->game_over[index]);
		pthread_mutex_unlock(&(d->monitor_mutex[index]));
	}
	return (ret);
}

int	ft_game_over(t_data *d, int philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(d->game_state));
	d->terminate = 1;
	while (i < d->number_of_philosophers)
	{
		if (philo - 1 == i)
			i++;
		pthread_mutex_lock(&(d->monitor_mutex[i]));
		d->game_over[i] = 1;
		pthread_mutex_unlock(&(d->monitor_mutex[i]));
		i++;
	}
	pthread_mutex_unlock(&(d->game_state));
	return (0);
}

int	check_philo(int *i, int now, int *full_phils, t_data *d)
{
	pthread_mutex_lock(&(d->monitor_mutex[*i]));
	if (now >= d->last_ate[*i] + d->time_to_die && now > 0)
		ft_print_status(d, _ded, (*i + 1));
	if (d->notepme > 0 && d->full[*i] == 1)
		(*full_phils)++;
	pthread_mutex_unlock(&(d->monitor_mutex[*i]));
	(*i)++;
	return (0);
}

void	*monitor_philos(void *args)
{
	int		i;
	int		now;
	int		full_phils;
	t_data	*d;

	d = (t_data *)args;
	while (ft_continue(d, -1))
	{
		i = 0;
		full_phils = 0;
		now = ft_get_ms(d);
		while (i < d->number_of_philosophers && ft_continue(d, -1))
		{
			check_philo(&i, now, &full_phils, d);
		}
		if (d->notepme > 0 && full_phils >= d->number_of_philosophers)
			ft_game_over(d, -1);
		usleep(5000 / d->number_of_philosophers);
	}
	return ((void *)0);
}
