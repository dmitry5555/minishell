/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 00:57:34 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/12 01:10:01 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// check if strings are identical
// return 0 if ok or difference for last character

int	ft_strcmp(const char *str1, const char *str2)
{
	unsigned int	i;

	if (!str1 || !str2)
		return (0);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
		{
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		}
		i++;
	}
	return (0);
}

//  first occurrence of any character
int	ft_strchars_i(const char *s, char *set)
{
	int				i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]))
			return (i);
		i++;
	}
	return (-1);
}

//  counts number of arguments X in arr[x][y]
int	nb_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

// writes char to fd
void	ft_putchar_fd(char ch, int fd)
{
	write(fd, &ch, 1);
}
