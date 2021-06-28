/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   union.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 19:20:06 by limartin      #+#    #+#                 */
/*   Updated: 2021/06/28 20:35:38 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int check_char(char *str, char c, int len)
{
	int j = 0;
	
	while (j < len)
	{
		if (str[j] == c)
			return(0) ;
		j++;
	}
	return (1);
}

int main (int argc, char **argv)
{
	if (argc == 3)
	{
		int str1_len = ft_strlen(argv[1]);
		int str2_len = ft_strlen(argv[2]);
		int i = 0; //index of input arg to check

		while (i < str1_len)
		{
			if (check_char(argv[1], argv[1][i], i))
				write(1, &(argv[1][i]), 1);
			i++;
		}
		i = 0;
		while (i < str2_len)
		{
			if (check_char(argv[1], argv[2][i], str1_len) && check_char(argv[2], argv[2][i], i))
				write(1, &(argv[2][i]), 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}