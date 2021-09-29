/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 15:08:19 by limartin      #+#    #+#                 */
/*   Updated: 2021/09/29 16:12:33 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_start_clock(t_data *d)
{
	gettimeofday(&(d->start_time), NULL);
	return (0);
}

int ft_get_ms(t_data *d)
{
	int	s;
	int	microS;
	int	miniS;
	struct timeval	now;

	gettimeofday(&now, NULL);
	s = (now.tv_sec - d->start_time.tv_sec);
	microS = (now.tv_usec - d->start_time.tv_usec);
	miniS = s * 1000 + microS / 1000;
	return ((int)miniS);
}
