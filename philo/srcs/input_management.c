/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_management.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:17:02 by lindsay       #+#    #+#                 */
/*   Updated: 2021/06/15 18:58:16 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int incorrect_arg_format(char *arg)
{
	printf("Parsing error: \n\
	Argument |%s| is incorrectly formatted.\n\
	Program will exit.\n", arg);
	return (1);
}

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

int ft_error_checker(int argc, char **argv, t_data *d)
{
	if (argc < 5 || argc > 6)
		return (incorrect_num_of_args());
	if (atoi_error(argv[1], &(d->number_of_philosophers)))
		return (incorrect_arg_format(argv[1]));
	if (atoi_error(argv[2], &(d->number_of_philosophers)))
		return (incorrect_arg_format(argv[2]));	
	if (atoi_error(argv[3], &(d->number_of_philosophers)))
		return (incorrect_arg_format(argv[3]));
	if (atoi_error(argv[4], &(d->number_of_philosophers)))
		return (incorrect_arg_format(argv[4]));
	if (argc == 6 && atoi_error(argv[5], &(d->number_of_philosophers)))
		return (incorrect_arg_format(argv[5]));
	return (0);
}