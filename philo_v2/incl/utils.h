/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 17:33:43 by lindsay       #+#    #+#                 */
/*   Updated: 2021/09/29 14:51:37 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>

char	*ft_itoa(int n);
int		atoi_error(const char *input, int *ptr);
int		are_strs_eq(const char *s1, const char *s2);
void	*e_malloc(size_t size);

#endif