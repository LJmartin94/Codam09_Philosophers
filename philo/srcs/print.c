/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 17:42:59 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/20 17:37:29 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_print_status(t_data *d, t_state reason, int philo_id)
{
	int	ms;

	pthread_mutex_lock(&(d->print_status));
	if (ft_continue(d, -1))
	{
		ms = ft_get_ms(d);
		if (reason == _ded)
		{
			printf(RED "%d Philo %d died\n" DEF, ms, philo_id);
			ft_game_over(d, philo_id);
		}
		else if (reason == _fork)
			printf(YLW "%d Philo %d has taken a fork\n" DEF, ms, philo_id);
		else if (reason == _eat)
			printf(GREEN "%d Philo %d is eating\n" DEF, ms, philo_id);
		else if (reason == _sleep)
			printf(BLUE "%d Philo %d is sleeping\n" DEF, ms, philo_id);
		else if (reason == _think)
			printf(CYAN "%d Philo %d is thinking\n" DEF, ms, philo_id);
	}
	pthread_mutex_unlock(&(d->print_status));
	return (0);
}
