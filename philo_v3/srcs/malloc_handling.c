/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/01 19:44:47 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/03 14:11:46 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_malloc_all(t_data *d)
{
// 	d->philosophers = (pthread_t *) \
// 	malloc(sizeof(pthread_t) * d->number_of_philosophers);
// 	d->args = (t_philo_thread_args *) \
// 	malloc(sizeof(t_philo_thread_args) * d->number_of_philosophers);
	d->forks = (pthread_mutex_t *) \
	malloc(sizeof(pthread_mutex_t) * d->number_of_philosophers);
// 	d->last_ate = (int *) \
// 	malloc(sizeof(int) * d->number_of_philosophers);
// 	d->full = (int *) \
// 	malloc(sizeof(int) * d->number_of_philosophers);
	if (!d->forks)
	// || !d->args || !d->philosophers || !d->last_ate \
	//|| !d->full)
		return (1);
	return (0);
}

int	ft_free_all(t_data *d)
{
	(void)d;
// 	free(d->philosophers);
// 	d->philosophers = NULL;
// 	free(d->args);
// 	d->args = NULL;
	free(d->forks);
	d->forks = NULL;
// 	free(d->last_ate);
// 	d->last_ate = NULL;
// 	free(d->full);
// 	d->full = NULL;
	return (0);
}

int	ft_malloc_failure(t_data *d)
{
	ft_free_all(d);
	printf("Memory allocation error: \n"
			"A malloc call failed to complete succesfully.\n"
			"Program will exit.\n");
	return (1);
}
