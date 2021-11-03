/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/01 19:44:47 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/03 18:28:08 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*res;
	size_t			i;

	res = (unsigned char *)malloc((size) * (count));
	if (!res)
		return (0);
	i = 0;
	while (i < (count * size))
	{
		res[i] = '\0';
		i++;
	}
	return (res);
}

int	ft_malloc_all(t_data *d)
{
	d->args = (t_philo_thread_args *) \
	ft_calloc(d->number_of_philosophers, sizeof(t_philo_thread_args));
	d->philosophers = (pthread_t *) \
	malloc(sizeof(pthread_t) * d->number_of_philosophers);
	d->forks = (pthread_mutex_t *) \
	malloc(sizeof(pthread_mutex_t) * d->number_of_philosophers);
	d->last_ate = (int *) \
	ft_calloc(d->number_of_philosophers, sizeof(int));
	d->full = (int *) \
	ft_calloc(d->number_of_philosophers, sizeof(int));
	if (!d->args || !d->philosophers || !d->forks || !d->last_ate \
		|| !d->full)
		return (1);
	return (0);
}

int	ft_free_all(t_data *d)
{
	free(d->args);
	d->args = NULL;
	free(d->philosophers);
	d->philosophers = NULL;
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
