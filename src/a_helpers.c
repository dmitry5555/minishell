/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:21:51 by justindaly        #+#    #+#             */
/*   Updated: 2023/10/21 18:08:18 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* move to lib? */
int	ft_a_len(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

void	ft_array_free(char ***array)
{
	int	i;

	i = 0;
	while (array && array[0] && array[0][i])
	{
		free(array[0][i]);
		i++;
	}
	if (array)
	{
		free(array[0]);
		*array = NULL;
	}
}

char	**ft_dup_array(char **array)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	n_rows = ft_a_len(array);
	out = malloc(sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	while (array[i])
	{
		out[i] = ft_strdup(array[i]);
		if (!out[i])
		{
			ft_array_free(&out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
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
	len = ft_a_len(in);
	out = malloc(sizeof(char *) * (len + 2));
	if (!out)
		return (in);
	while (++i < len)
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
		{
			ft_array_free(&in);
			ft_array_free(&out);
		}
	}
	out[i] = ft_strdup(newstr);
	out[len + 1] = NULL;
	ft_array_free(&in);
	return (out);
}

// void	ft_print_array(char **array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i])
// 	{
// 		printf("array[%d] = %s\n", i, array[i]);
// 		i++;
// 	}
// }