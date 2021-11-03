/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 17:42:59 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/03 19:28:17 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	cp_print_status(t_data *d, t_state reason, int philo_id, char mode)
{
	int	ms;

	ms = ft_get_ms(d);
	if (reason == _ded)
	{
		printf(RED "%d Philo %d died\n" DEF, ms, philo_id);
		cp_game_over(d, mode);
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

int cp_request_print(t_data *d, t_state reason, int philo_id, char mode)
{
	int go_ret;

	go_ret = 0;
	pthread_mutex_lock(&(d->print_status));
	go_ret = cp_continue(d, mode);
	if (go_ret)
		cp_print_status(d, reason, philo_id, mode);
	pthread_mutex_unlock(&(d->print_status));
	return (go_ret);
}
