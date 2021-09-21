/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:35:34 by lindsay       #+#    #+#                 */
/*   Updated: 2021/09/21 17:44:16 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include "utils.h"

typedef struct s_data
{
	int number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;

	pthread_mutex_t *game_state;
	pthread_mutex_t *print_status;
	// pthread_mutex_t *action_mutex;
	// int this_thread;
} t_data;

typedef struct s_philo_thread_args
{
	int 	thread_id;
	t_data	*d;
} t_philo_thread_args;

int ft_error_checker(int argc, char **argv, t_data *d);

#endif