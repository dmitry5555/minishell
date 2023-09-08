/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:24:48 by jdaly             #+#    #+#             */
/*   Updated: 2023/09/08 16:46:34 by jdaly            ###   ########.fr       */
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
			flag_rd = 0;
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

char	**ft_subsplit(char **array, char *set, int i)
{
	char **subarray;

	while (array && array[++i])
	{
		if (array[i][0] != '\'' && array[i][0] != '"')
		{
			if (ft_sub_count_words(array[i], set) > 1)
			{
				//printf("countwords = %d\n", ft_sub_count_words(array[i], "<|>"));
				subarray = ft_sub_create_array(array[i], set, ft_sub_count_words(array[i], set));
				//print_array(subarray);
				array = ft_array_replace_in(&array, subarray, i);
				//print_array(array);
			}
		}
	}
	ft_array_free(&subarray);
	return (array);
}

// int main(void)
// {
//     char    **subarray;
//     int     wordcount;
//     char    *str = "|hello|>ldkja>a";

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

// int	main(void)
// {
// 	char **array = malloc(sizeof(char *) * (3 + 1));
//     array[0] = strdup("'hello|>'");
//     array[1] = strdup("|a>");
//     array[2] = strdup("str<ing|>Makefile");
//     array[3] = NULL;

// 	print_array(array);
// 	array = ft_subsplit(array, "<|>", -1);
// 	print_array(array);
// }