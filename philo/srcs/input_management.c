/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_management.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:17:02 by lindsay       #+#    #+#                 */
/*   Updated: 2021/06/15 16:57:16 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int incorrect_num_of_args(void)
{
	printf("Incorrect number of arguments specified.\n\
You must supply 4 5 arguments, namely:\n \
	1) number_of_philosophers\n \
	2) time_to_die\n \
	3) time_to_eat\n \
	4) time_to_sleep\n \
	5) (OPTIONAL) number_of_times_each_philosopher_must_eat\n");
	return (1);
}

int ft_error_checker(int argc, char **argv)
{
	(void)argv;
	if (argc < 5 || argc > 6)
		return (incorrect_num_of_args());
	return (0);
}