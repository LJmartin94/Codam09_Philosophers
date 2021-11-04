/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:35:34 by lindsay       #+#    #+#                 */
/*   Updated: 2021/11/04 00:50:56 by limartin      ########   odam.nl         */
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

// # define RED ""
// # define GREEN ""
// # define BLUE ""
// # define YLW ""
// # define CYAN ""
// # define DEF ""

typedef enum e_state
{
	_think,
	_fork,
	_eat,
	_sleep,
	_ded
}	t_state;

typedef struct s_philo_thread_args
{
	struct s_data	*d;
	int				thread_id;
	int				philo;
	t_state			state;
	int				forks_held;
	int				times_ate;
	int				first_fork;
	int				second_fork;
}	t_philo_thread_args;

typedef struct s_data
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					notepme;
	pthread_mutex_t		game_state;
	int					game_state_init;
	pthread_mutex_t		print_status;
	int					print_status_init;
	pthread_mutex_t		*forks;
	int					forks_initialised;
	t_philo_thread_args	*args;
	pthread_t			*philosophers;
	struct timeval		start_time;
	pthread_t			monitor;
	int					p_terminate;
	int					*p_last_ate;
	int					*p_full;
}	t_data;

int		ft_data_null(t_data *d);
int		ft_error_checker(int argc, char **argv, t_data *d);
int		ft_malloc_all(t_data *d);
int		ft_malloc_failure(t_data *d);
int		ft_free_all(t_data *d);
int		ft_create_all_mutexes(t_data *d);
int		ft_destroy_all_mutexes(t_data *d);
int		c_create_threads(t_data *d);
int		c_kill_all_threads(t_data *d);
void	*c_philosophise(void *args);
void	*c_monitor_philos(void *args);
int		cp_continue(t_data *d, char mode);
int		cp_game_over(t_data *d, char mode);
int		ft_start_clock(t_data *d);
int		ft_get_ms(t_data *d);
int		cp_request_print(t_data *d, t_state reason, int philo_id, char mode);
int		c_try_forks(t_philo_thread_args *pta, int *last_ate);
int		ft_drop_forks(t_data *d, int philo, int *forks_held);
int		accusleep(t_data *d, int micro_target);

#endif