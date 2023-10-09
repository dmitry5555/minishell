/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:24:48 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/09 19:28:58 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_sub_count_words(const char *s, char *set, int i)
{
	int	in_sq;
	int	in_dq;
	int	nwords;

	in_sq = 0;
	in_dq = 0;
	nwords = 0;
	while (s && s[i] != '\0')
	{
		nwords++;
		if (!ft_strchr(set, s[i]))
		{
			while ((!ft_strchr(set, s[i]) || in_sq || in_dq) && s[i] != '\0')
			{
				in_sq = (in_sq + (!in_dq && s[i] == '\'')) % 2;
				in_dq = (in_dq + (!in_sq && s[i] == '\"')) % 2;
				i++;
			}
			if (in_sq || in_dq)
				return (-1);
		}
		else
			i++;
	}
	return (nwords);
}

static char	**ft_sub_fill_array(char **array, const char *s, char *set,
		int i[2])
{
	int	str_len;
	int	word_start;
	int	in_q[2];

	str_len = ft_strlen(s);
	in_q[0] = 0;
	in_q[1] = 0;
	while (s && s[i[0]] != '\0')
	{
		word_start = i[0];
		if (!ft_strchr(set, s[i[0]]))
		{
			while ((!ft_strchr(set, s[i[0]]) || in_q[0] || in_q[1]) && s[i[0]])
			{
				in_q[0] = (in_q[0] + (!in_q[1] && s[i[0]] == '\'')) % 2;
				in_q[1] = (in_q[1] + (!in_q[0] && s[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		array[i[1]++] = ft_substr(s, word_start, i[0] - word_start);
	}
	array[i[1]] = NULL;
	return (array);
}

char	**ft_subsplit(const char *s, char *set)
{
	char	**array;
	int		nwords;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	if (!s)
		return (NULL);
	nwords = ft_sub_count_words(s, set, 0);
	if (nwords == -1)
		return (NULL);
	array = malloc((nwords + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = ft_sub_fill_array(array, s, set, 0);
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

// 	ft_print_array(array);
// 	array = ft_subsplit(array, "<|>", -1);
// 	ft_print_array(array);
// 	ft_array_free(&array);
// }