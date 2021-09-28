/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 17:28:13 by limartin      #+#    #+#                 */
/*   Updated: 2021/09/28 18:15:37 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Guarantees all data in the data struct initially set to NULL
int ft_data_null(t_data *d)
{
    d->number_of_philosophers = -1;
	d->time_to_die = -1;
	d->time_to_eat = -1;
	d->time_to_sleep = -1;
	d->number_of_times_each_philosopher_must_eat = -1;

    d->allocation_failure = 0;

	d->game_state = NULL;
	d->print_status = NULL;

    d->philosophers = NULL;
    d->args = NULL;
    return (0);
}

int ft_malloc_all(t_data *d)
{
    d->philosophers = (pthread_t *)malloc(sizeof(pthread_t) * d->number_of_philosophers); //malloc philo array
	d->args = (t_philo_thread_args *)malloc(sizeof (t_philo_thread_args) * d->number_of_philosophers); //malloc philo args
    if (!d->philosophers || !d->args)
        d->allocation_failure = 1;
    return(0);
}

int ft_free_all(t_data *d)
{
    (void) d;
    return(0);
}

int ft_create_all_mutexes(t_data *d)
{
    (void) d;
    return (0);
}

int ft_destroy_all_mutexes(t_data *d)
{
    (void) d;
    return (0);
}