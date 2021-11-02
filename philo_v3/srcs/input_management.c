/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_management.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 16:17:02 by lindsay       #+#    #+#                 */
/*   Updated: 2021/11/02 18:07:17 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	invalid_arg(void)
{
	printf("Error: Invalid argument passed. \n"
	"All arguments should be greater than or equal to zero, "
	"and there should be 1 to 200 philosophers.\n"
	"If specified, number_of_times_each_philosopher_must_eat "
	"must be greater than zero.\n");
	return (1);
}

static int	incorrect_arg_format(char *arg)
{
	printf("Parsing error: \n"
	"Argument |%s| is incorrectly formatted.\n"
	"Program will exit.\n", arg);
	return (1);
}

static int	incorrect_num_of_args(void)
{
	printf("Error: Incorrect number of arguments specified.\n"
	"You must supply 4-5 arguments, namely:\n"
	"1) number_of_philosophers\n"
	"2) time_to_die\n"
	"3) time_to_eat\n"
	"4) time_to_sleep\n"
	"5) (OPTIONAL) number_of_times_each_philosopher_must_eat\n");
	return (1);
}

int	ft_error_checker(int argc, char **argv, t_data *d)
{
	d->notepme = -1;
	if (argc < 5 || argc > 6)
		return (incorrect_num_of_args());
	if (atoi_error(argv[1], &(d->number_of_philosophers)))
		return (incorrect_arg_format(argv[1]));
	if (atoi_error(argv[2], &(d->time_to_die)))
		return (incorrect_arg_format(argv[2]));
	if (atoi_error(argv[3], &(d->time_to_eat)))
		return (incorrect_arg_format(argv[3]));
	if (atoi_error(argv[4], &(d->time_to_sleep)))
		return (incorrect_arg_format(argv[4]));
	if (argc == 6 && atoi_error(argv[5], \
	&(d->notepme)))
		return (incorrect_arg_format(argv[5]));
	if (d->number_of_philosophers <= 0 || d->number_of_philosophers > 200 || \
	d->time_to_die < 0 || d->time_to_eat < 0 || d->time_to_sleep < 0 || \
	(d->notepme <= 0 && argc == 6))
		return (invalid_arg());
	return (0);
}
