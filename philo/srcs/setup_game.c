/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 17:28:13 by limartin      #+#    #+#                 */
/*   Updated: 2021/10/12 23:32:10 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Guarantees all data in the data struct initially set to NULL
int	ft_data_null(t_data *d)
{
	d->number_of_philosophers = -1;
	d->time_to_die = -1;
	d->time_to_eat = -1;
	d->time_to_sleep = -1;
	d->notepme = -1;
	d->game_state_init = 0;
	d->print_status_init = 0;
	d->last_ate_init = 0;
	d->forks_initialised = 0;
	d->philosophers = NULL;
	d->args = NULL;
	d->forks = NULL;
	d->clock_started = 0;
	d->terminate = 0;
	return (0);
}
