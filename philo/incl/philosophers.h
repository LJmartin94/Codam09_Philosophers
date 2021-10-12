/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:35:34 by lindsay       #+#    #+#                 */
/*   Updated: 2021/10/12 19:14:01 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "utils.h"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define YLW "\033[0;33m"
# define CYAN "\033[0;36m"
# define DEF "\033[0m"

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
	pthread_t			*philosophers;
	pthread_t			monitor;
	t_philo_thread_args	*args;
	struct timeval		start_time;
	int					terminate;
	int					*last_ate;
	pthread_mutex_t		game_state;
	pthread_mutex_t		print_status;
	pthread_mutex_t		mutex_last_ate;
	pthread_mutex_t		*forks;
	int					game_state_init;
	int					print_status_init;
	int					last_ate_init;
	int					forks_initialised;
	int					clock_started;
}	t_data;

int	ft_error_checker(int argc, char **argv, t_data *d);
int	ft_data_null(t_data *d);
int	ft_malloc_all(t_data *d);
int	ft_free_all(t_data *d);
int	ft_create_all_mutexes(t_data *d);
int	ft_destroy_all_mutexes(t_data *d);
int	ft_start_clock(t_data *d);
int	ft_get_ms(t_data *d);
int	ft_print_status(t_data *d, t_state reason, int philo_id);
int	ft_kill_all_threads(t_data *d);
int	ft_malloc_failure(t_data *d);
int	ft_mutex_init_failure(t_data *d);
int	ft_mutex_destroy_failure(t_data *d);
int ft_try_forks(t_data *d, int philo, int now, int *forks_held);
int ft_drop_forks(t_data *d, int philo, int *forks_held);
void	*monitor_philos(void *args);

#endif