/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 17:42:59 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/01 19:57:08 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_print_status(t_data *d, t_state reason, int philo_id, int unused)
{
	int	ms;

	(void)unused;
	ms = ft_get_ms(d);
	if (reason == _ded)
	{
		printf(RED "%d Philo %d died\n" DEF, ms, philo_id);
		ft_game_over(d, philo_id);
	}
	else if (reason == _fork)
		printf(YLW "%d Philo %d has taken a fork\n" DEF, ms, philo_id);
	else if (reason == _eat)
	{
		printf(YLW "%d Philo %d has taken a fork\n" DEF, ms, philo_id);
		printf(GREEN "%d Philo %d is eating\n" DEF, ms, philo_id);
	}
	else if (reason == _sleep)
		printf(BLUE "%d Philo %d is sleeping\n" DEF, ms, philo_id);
	else if (reason == _think)
		printf(CYAN "%d Philo %d is thinking\n" DEF, ms, philo_id);
	return (0);
}

int ft_request_print(t_data *d, t_state reason, int philo_id, int authority)
{
	if (authority == 0)
	{
		pthread_mutex_lock(&(d->print_status));
		if (ft_continue(d, -1))
			ft_print_status(d, reason, philo_id, authority);
		pthread_mutex_unlock(&(d->print_status));
	}
	else if (authority == 1)
	{
		pthread_mutex_lock(&(d->print_status));
		if (!(d->terminate))
			ft_print_status(d, reason, philo_id, authority);
		pthread_mutex_unlock(&(d->print_status));
	}
	return (0);
}
