/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 13:42:13 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/03 22:20:19 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	cp_continue(t_data *d, char mode)
{
	int	ret;

	if (mode == 'p')
		return(!(d->p_terminate));
	if (mode == 'c')
	{
		pthread_mutex_lock(&(d->game_state));
		ret = !(d->p_terminate);
		pthread_mutex_unlock(&(d->game_state));
		return (ret);
	}
	return(0);
}

int	cp_game_over(t_data *d, char mode)
{
	if (mode == 'p')
		d->p_terminate = 1;
	else if (mode == 'c')
	{
		pthread_mutex_lock(&(d->game_state));
		d->p_terminate = 1;
		pthread_mutex_unlock(&(d->game_state));
	}
	return (0);
}

int	p_check_philo(int *i, int now, int *full_phils, t_data *d)
{
	int ret;

	ret = 1;
	if (now >= d->p_last_ate[*i] + d->time_to_die && now > 0)
	{
		pthread_mutex_unlock(&(d->game_state));
		ret = cp_request_print(d, _ded, (*i + 1), 'c');
		pthread_mutex_lock(&(d->game_state));
	}
	if (d->notepme > 0 && d->p_full[*i] == 1)
		(*full_phils)++;
	(*i)++;
	return (ret);
}

void	*c_monitor_philos(void *args)
{
	t_data	*d;
	int		i;
	int		now;
	int		full_phils;
	int		go;

	d = (t_data *)args;

	go = cp_continue(d, 'c');
	while (go)
	{
		i = 0;
		full_phils = 0;
		now = ft_get_ms(d);
		pthread_mutex_lock(&(d->game_state));
		while (i < d->number_of_philosophers)
			go = p_check_philo(&i, now, &full_phils, d);
		if (d->notepme > 0 && full_phils >= d->number_of_philosophers)
			go = cp_game_over(d, 'p');
		pthread_mutex_unlock(&(d->game_state));
		usleep(5000);
	}
	return ((void *)0);
}
