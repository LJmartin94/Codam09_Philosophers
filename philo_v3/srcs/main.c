/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:13:22 by lindsay       #+#    #+#                 */
/*   Updated: 2021/11/03 18:44:22 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	d;

	ft_data_null(&d);
	if (ft_error_checker(argc, argv, &d))
		return (1);
	if (ft_malloc_all(&d))
		return (ft_malloc_failure(&d));
	if (ft_create_all_mutexes(&d))
		return (1);
	if (c_create_threads(&d))
		return (1);
	while (cp_continue(&d, 'c'))
		usleep(1000);
	c_kill_all_threads(&d);
	ft_destroy_all_mutexes(&d);
	ft_free_all(&d);
	return (0);
}
