/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 15:08:19 by limartin      #+#    #+#                 */
/*   Updated: 2021/11/04 00:55:04 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	unsigned int	now;
	double			delay_factor;
	double			quart;

	micro_target = micro_target * 9 / 10;
	start = ft_get_micros(d);
	target_time = start + micro_target;
	usleep(micro_target / 4);
	now = ft_get_micros(d);
	quart = now - start;
	delay_factor = quart / (micro_target / 4);
	if (delay_factor >= 2.0)
		usleep((micro_target - quart) / delay_factor);
	else
		usleep(micro_target - quart);
	while(ft_get_micros(d) < target_time)
		usleep(micro_target / 10);
	return(0);
}
