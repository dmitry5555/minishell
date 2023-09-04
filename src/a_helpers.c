/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justindaly <justindaly@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:21:51 by justindaly        #+#    #+#             */
/*   Updated: 2023/09/04 16:44:26 by justindaly       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* move to lib? */
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

int	ft_array_len(char **array)
{
	int	i;
	i = 0;
	while (array && array[i])
		i++;
    return (i);
}

void	print_array(char **array)
{
	int	i;
	i = 0;
	while (array[i])
	{
		printf("array[%d] = %s\n", i, array[i]);
		i++;
	}
}

void	ft_array_free(char **array)
{
	int	i;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_array_replace_in(char ***array, char **subarray, int n)
{
	char	**tmp_array;
	int     i;
    int     j;
    int     k;

	i = -1;
	j = -1;
	k = -1;
	if (!array || !*array || n < 0 || n >= ft_arraylen(*array))
		return (NULL);
	tmp_array = ft_calloc(ft_arraylen(*array) + ft_arraylen(subarray) + 1, sizeof(char *));
    if (!tmp_array)
        return (NULL);
	while ((*array)[++i])
	{
		if (i != n)
			tmp_array[++k] = ft_strdup((*array)[i]);
		else
		{
			while (subarray && subarray[++j])
				tmp_array[++k] = ft_strdup(subarray[j]);
		}
	}
    tmp_array[++k] = NULL;
	ft_free_array(*array);
	*array = tmp_array;
	return (*array);
}

char	**ft_array_extend(char **in, char *newstr)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!newstr)
		return (in);
	len = ft_array_len(in);
	out = malloc(sizeof(char *) * (len + 2));
	out[len + 1] = NULL;
	if (!out)
		return (in);
	while (++i < len)
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
		{
			ft_free_array(&in);
			ft_array_free(&out);
		}
	}
	out[i] = ft_strdup(newstr);
	ft_free_matrix(&in);
	return (out);
}