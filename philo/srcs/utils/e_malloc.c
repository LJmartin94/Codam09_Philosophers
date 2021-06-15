/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   e_malloc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/15 17:47:33 by lindsay       #+#    #+#                 */
/*   Updated: 2021/06/15 18:49:17 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void *e_malloc(size_t size)
{
	void	*res;
	int		wv;

	res = malloc(size);
	if (res == NULL)
	{
		wv = write(2, "A malloc error occurred and the program terminated.\n", 53);
		(void)wv;
		exit(errno);
	}
	else
		return(res);
}