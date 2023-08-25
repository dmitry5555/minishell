/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justindaly <justindaly@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:24:48 by jdaly             #+#    #+#             */
/*   Updated: 2023/08/25 17:52:03 by justindaly       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int ft_sub_count_words(char *str, char *set) 
{
    int wordcount;
    int i;
    int flag_rd;

	i = -1;
	wordcount = 0;
	flag_rd = 0;
	while (str[++i])
	{
		// Start reading a word if not the delimiter '|'
		if (!flag_rd && !ft_strchr(set, str[i]))
		{
			flag_rd = 1;
			wordcount++;
		}
		// Reach the end of a word if the delimiter '|', or end of the string
		else if (flag_rd && (ft_strchr(set, str[i]) || str[i + 1] == '\0'))
		{
			wordcount++;
			flag_rd = 0;
		}
		if (ft_strchr(set, str[i]))
			wordcount++;
	}
    return wordcount;
}

static char	**ft_sub_create_array(char *str, char *set, int wordcount)
{
    int     i;
    int     j;
    int     flag_rd = 0;
    int     start = 0;
    char    **array;

    array = malloc(sizeof(char *) * (wordcount + 1));
	if (!array)
		return (NULL);
	i = -1;
	j = -1;
    while (str[++i])
    {
        // Start reading a word if not the delimiter '|'
        if (!flag_rd && !ft_strchr(set, str[i]))
        {
            flag_rd = 1;
            start = i;
        }
        // Reach the end of a word if the delimiter '|', or end of the string
        if (flag_rd && ft_strchr(set, str[i]))
        {
            array[++j] = ft_strndup(&str[start], i - start);
            flag_rd = 0;
        }
        if (flag_rd && str[i + 1] == '\0')
        {
            array[++j] = ft_strndup(&str[start], i - start + 1);
            flag_rd = 0;
        }
        if (ft_strchr(set, str[i]))
            array[++j] = ft_strndup(&str[i], 1);
    }
    array[++j] = NULL;
    return (array);
}

int ft_arraylen(char **array)
{
	int	i;
	i = 0;
	while (array && array[i])
		i++;
    return (i);
}
void	ft_free_array(char **array)
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
	tmp_array = ft_calloc(ft_arraylen(*array) + ft_arraylen(subarray), sizeof(char *));
    if (!tmp_array)
        return (NULL);
	while ((*array)[++i])
	{
		tmp_array[++k] = ft_strdup((*array)[i]);
		if (i == n)
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

// int main(void)
// {
//     char    **subarray;
//     int     wordcount;
//     char    *str = "|exit>Makefile >|>dog";

//     wordcount = ft_sub_count_words(str, "<|>");
//     printf("wordcount = %d\n", wordcount);
//     subarray = ft_sub_create_array(str, "<|>", wordcount);
//     print_array(subarray);
// }

// int main(void)
// {
//     char **array;
//     char **subarray;

//     array = malloc(sizeof(char *) * (3 + 1));
//     array[0] = strdup("hello");
//     array[1] = strdup("a");
//     array[2] = strdup("string");
//     array[3] = NULL;

//     subarray = malloc(sizeof(char *) * (2 + 1));
//     subarray[0] = strdup("this");
//     subarray[1] = strdup("is");
//     subarray[2] = NULL;

//     print_array(array);
//     print_array(subarray);
//     array = ft_array_replace_in(&array, subarray, 0);
//     printf("array length = %d\n", ft_arraylen(array));
//     print_array(array);
// }