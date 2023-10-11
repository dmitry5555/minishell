/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_helpers2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:45:35 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/11 22:59:14 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_bzero(void *s, size_t n)
{
	char	*c;
	size_t	i;

	c = s;
	i = 0;
	while (i < n)
	{
		c[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size == SIZE_MAX || count == SIZE_MAX)
		return (0);
	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, (count * size));
	return (ptr);
}

char	**ft_array_replace_in(char ***a, char **sub, int n)
{
	char	**tmp_array;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!a || !*a || n < 0 || n >= ft_a_len(*a))
		return (NULL);
	tmp_array = ft_calloc(ft_a_len(*a) + ft_a_len(sub) + 1, sizeof(char *));
	if (!tmp_array)
		return (NULL);
	while ((*a)[++i[0]])
	{
		if (i[0] != n)
			tmp_array[++i[2]] = ft_strdup((*a)[i[0]]);
		else
		{
			while (sub && sub[++i[1]])
				tmp_array[++i[2]] = ft_strdup(sub[i[1]]);
		}
	}
	tmp_array[++i[2]] = NULL;
	ft_array_free(a);
	*a = tmp_array;
	return (*a);
}
