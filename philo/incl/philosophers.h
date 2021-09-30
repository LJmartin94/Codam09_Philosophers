/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:35:34 by lindsay       #+#    #+#                 */
/*   Updated: 2021/09/30 20:58:28 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "utils.h"

# define COLOUR_RED "\033[0;31m"
# define COLOUR_GREEN "\033[0;32m"
# define COLOUR_BLUE "\033[0;34m"
# define COLOUR_YELLOW "\033[0;33m"
# define COLOUR_CYAN "\033[0;36m"
# define COLOUR_DEFAULT "\033[0m"

typedef enum e_state
{
	_fork,
	_eat,
	_sleep,
	_think,
	_ded
}	t_state;

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
	struct timeval		start_time;
	int					terminate;
	pthread_mutex_t		game_state;
	pthread_mutex_t		print_status;
	int					game_state_init;
	int					print_status_init;
}	t_data;

int	ft_error_checker(int argc, char **argv, t_data *d);
int	ft_data_null(t_data *d);
int	ft_malloc_all(t_data *d);
int	ft_free_all(t_data *d);
int	ft_create_all_mutexes(t_data *d);
int	ft_destroy_all_mutexes(t_data *d);
int ft_start_clock(t_data *d);
int ft_get_ms(t_data *d);
int ft_print_status(t_data *d, t_state reason, int philo_id);
int	ft_kill_all_threads(t_data *d);

#endif