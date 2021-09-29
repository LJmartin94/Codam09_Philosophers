/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:35:34 by lindsay       #+#    #+#                 */
/*   Updated: 2021/09/29 15:02:29 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include "utils.h"

typedef struct s_philo_thread_args
{
	int				thread_id;
	struct s_data	*d;
}	t_philo_thread_args;

typedef struct s_data
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					allocation_failure;
	pthread_t			*philosophers;
	t_philo_thread_args	*args;
	pthread_mutex_t		game_state;
	int					game_state_init;
	pthread_mutex_t		print_status;
	int					print_status_init;
}	t_data;

int	ft_error_checker(int argc, char **argv, t_data *d);
int	ft_data_null(t_data *d);
int	ft_malloc_all(t_data *d);
int	ft_free_all(t_data *d);
int	ft_create_all_mutexes(t_data *d);
int	ft_destroy_all_mutexes(t_data *d);

#endif