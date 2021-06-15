/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 17:18:42 by lindsay       #+#    #+#                 */
/*   Updated: 2021/06/15 18:23:29 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** Helper function for itoa to determine number of characters to malloc.
*/

static	size_t	ft_intlen(long int num)
{
	size_t		len;

	len = 0;
	if (num <= 0)
		len++;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

/*
** Returns a malloc'd string based on the integer passed.
*/

char			*ft_itoa(int n)
{
	long int	num;
	size_t		len;
	size_t		i;
	char		*res;

	num = n;
	len = ft_intlen(num);
	res = (char *)e_malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		res[i] = '-';
		num *= -1;
		i++;
	}
	res[len] = '\0';
	while (len != i)
	{
		len--;
		res[len] = (num % 10) + '0';
		num /= 10;
	}
	return (res);
}

/*
** Behaves like standard atoi function, used in 'atoi_error' wrapper function.
*/

static int		ft_atoi(const char *str)
{
	int			i;
	long int	sign;
	long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	if ((i > 0) && (str[i - 1] == '-'))
		sign = -1;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		if (((str[i] - '0') + (res * 10)) < res)
			return (((-1 * sign) - 1) / 2);
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return ((int)(res * sign));
}

/*
** Runs atoi, and saves the number passed as string into the int ptr passed. 
** The function returns 1 on overflow or 0 if the conversion was succesful.
** Arguments with leading zeros or plusses are not handled.
*/

int atoi_error(const char *input, int *ptr)
{
	int		test;
	char	*expected;
	
	test = ft_atoi(input);
	expected = ft_itoa(test);
	if (are_strs_eq(expected, input))
	{
		free(expected);
		*ptr = test;
		return (0);
	}
	free(expected);
	return (1);
}