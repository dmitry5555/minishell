/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:24:48 by jdaly             #+#    #+#             */
/*   Updated: 2023/08/24 18:46:35 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int ft_sub_count_words(char *str) 
{
    int wordcount = 0;
    int i = 0;
    int flag_rd = 0;

    while (str[i])
    {
        // Start reading a word if not the delimiter '|'
        if (!flag_rd && str[i] != '|')
            flag_rd = 1;
        // Reach the end of a word if the delimiter '|', or end of the string
        if (flag_rd && (str[i] == '|' || str[i + 1] == '\0'))
        {
            wordcount++;
            flag_rd = 0;
        }
        if (str[i] == '|')
            wordcount++;
        i++;
    }
    return wordcount;
}

static char	**ft_sub_create_array(char *str, int wordcount)
{
    int     i = 0;
    int     j = 0;
    int     flag_rd = 0;
    int     start = 0;
    char    **array;

    array = malloc(sizeof(char *) * (wordcount + 1));
	if (!array)
		return (NULL);
    while (str[i])
    {
        // Start reading a word if not the delimiter '|'
        if (!flag_rd && str[i] != '|')
        {
            flag_rd = 1;
            start = i;
        }
        // Reach the end of a word if the delimiter '|', or end of the string
        if (flag_rd && str[i] == '|')
        {
            array[j++] = ft_strndup(&str[start], i - start);
            flag_rd = 0;
        }
        if (flag_rd && str[i + 1] == '\0')
        {
            array[j++] = ft_strndup(&str[start], i - start + 1);
            flag_rd = 0;
        }
        if (str[i] == '|')
            array[j++] = strdup("|");
       i++;
    }
    array[j] = NULL;
    return (array);
}
	// char **array;
	// int	start = 0;
	// int	i = 0;
	// int	j = 0;
	// int	flag_sq = 0;
	// int	flag_dq = 0;
	// int	flag_rd = 0;

	// array = malloc(sizeof(char *) * (wordcount + 1));
	// if (!array)
	// 	return (NULL);
	// while (str[i])
	// {
	// 	if (str[i] == 39 && !flag_dq) // single
	// 	{
	// 		if (!flag_sq)
	// 		{
	// 			flag_sq = 1;
	// 			start = i;
	// 		}
	// 		else
	// 		{
	// 			array[j++] = ft_strndup(&str[start], i - start + 1);
	// 			flag_sq = 0;
	// 			start = -1;
	// 		}

	// 	}

	// 	if (str[i] == 34 && !flag_sq) // double
	// 	{
	// 		if (!flag_dq)
	// 		{
	// 			flag_dq = 1;
	// 			start = i;
	// 		}
	// 		else
	// 		{
	// 			array[j++] = ft_strndup(&str[start], i - start + 1);
	// 			flag_dq = 0;
	// 			start = -1;
	// 		}

	// 	}

	// 	if (str[i] && !flag_sq && !flag_dq && str[i] != 34 && str[i] != 39)
	// 	{
	// 		// if not space start reading
	// 		if (!flag_rd && str[i] != '|')
	// 		{
	// 			// printf("last word start\\n");
	// 			flag_rd = 1;
	// 			start = i;
	// 		}
	// 		// reach the end of word - if next one is space or quotes or EOL
	// 		if (flag_rd && (str[i+1] == '|' || str[i+1] == 34 || str[i+1] == 39 || !str[i+1]))
	// 		{
	// 			// printf("last word end\\n");
	// 			array[j++] = ft_strndup(&str[start], i - start + 1);
	// 			flag_rd = 0;
	// 		}
	// 	}
    //     if (str[i] == '|' && !flag_dq && !flag_sq)
    //         array[j++] = strdup("|");
	// 	i++;
	// }
// 	// return (array);

// }

// static void	print_array(char **array)
// {
// 	int	i;
// 	i = 0;
// 	while (array[i])
// 	{
// 		printf("array[%d] = %s\n", i, array[i]);
// 		i++;
// 	}
// }

// int main(void)
// {
//     char    **subarray;
//     int     wordcount;
//     char    *str = "|exit|Makefile";

//     wordcount = ft_sub_count_words(str);
//     printf("wordcount = %d\n", wordcount);
//     subarray = ft_sub_create_array(str, wordcount);
//     print_array(subarray);
// }