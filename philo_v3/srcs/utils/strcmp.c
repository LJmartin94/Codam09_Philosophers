/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strcmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/22 20:28:41 by lindsay       #+#    #+#                 */
/*   Updated: 2021/11/02 17:10:05 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h" 

// size_t	ft_strlen(const char *s)
// {
// 	size_t	len;

// 	len = 0;
// 	while (s[len] != '\0')
// 		len++;
// 	return (len);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t			i;
// 	int				res;
// 	unsigned char	c1;
// 	unsigned char	c2;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (s1[i] == s2[i])
// 	{
// 		if (((s1[i] == '\0') && (s2[i] == '\0')) || (i == n - 1))
// 			return (0);
// 		i++;
// 	}
// 	c1 = (unsigned char)s1[i];
// 	c2 = (unsigned char)s2[i];
// 	res = (c1 - c2);
// 	return (res);
// }

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	int	n;

// 	n = ft_strlen(s1);
// 	return (ft_strncmp(s1, s2, n + 1));
// }

// int	are_strs_eq(const char *s1, const char *s2)
// {
// 	if (ft_strcmp(s1, s2) != 0)
// 		return (0);
// 	else
// 		return (1);
// }
