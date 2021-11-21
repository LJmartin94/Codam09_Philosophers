/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 15:08:19 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/21 16:07:31 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <time.h>

int	ft_start_clock(t_data *d)
{
	gettimeofday(&(d->start_time), NULL);
	return (0);
}

int	ft_get_ms(t_data *d)
{
	int				s;
	int				microS;
	int				miniS;
	struct timeval	now;

	gettimeofday(&now, NULL);
	s = (now.tv_sec - d->start_time.tv_sec);
	microS = (now.tv_usec - d->start_time.tv_usec);
	miniS = s * 1000 + microS / 1000;
	return ((int)miniS);
}

unsigned int	ft_get_micros(t_data *d)
{
	unsigned int	s;
	unsigned int	microS;
	struct timeval	now;

	gettimeofday(&now, NULL);
	s = (now.tv_sec - d->start_time.tv_sec);
	microS = (now.tv_usec - d->start_time.tv_usec);
	microS = s * 1000000 + microS;
	return (microS);
}

int	accusleep(t_data *d, int micro_target)
{
	unsigned int	start;
	unsigned int	target_time;

	start = ft_get_micros(d);
	target_time = start + micro_target;
	if (ft_get_micros(d) < target_time)
		usleep((micro_target / 2) + (micro_target / 4));
	while (ft_get_micros(d) < target_time)
		usleep(micro_target / 8);
	return (0);
}
