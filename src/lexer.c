/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:45:49 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/09 18:36:20 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* lexer analysis
1. split and remove whitespace */
static int	ft_count_words(const char *str, char *set, int i, int in_quotes)
{
	int		nwords;
	char	quote_type;

	nwords = 0;
	quote_type = 0;
	while (str[i] != '\0')
	{
		if (!ft_strchr(set, str[i]) && (++nwords))
		{
			while ((!ft_strchr(set, str[i]) || in_quotes) && str[i] != '\0')
			{
				if (!quote_type && (str[i] == '\"' || str[i] == '\''))
					quote_type = str[i];
				in_quotes = (in_quotes + (str[i] == quote_type)) % 2;
				if (!in_quotes)
					quote_type *= 0;
				i++;
			}
			if (in_quotes)
				return (-1);
		}
		else
			i++;
	}
	return (nwords);
}

static char	**ft_fill_array(char **array, const char *str, char *set,
		int in_q[2])
{
	int	str_len;
	int	word_start;
	int	i[2];

	str_len = ft_strlen(str);
	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		while (ft_strchr(set, str[i[0]]) && str[i[0]] != '\0')
			i[0]++;
		word_start = i[0];
		while ((!ft_strchr(set, str[i[0]]) || in_q[0] || in_q[1]) && str[i[0]])
		{
			in_q[0] = (in_q[0] + (!in_q[1] && str[i[0]] == '\'')) % 2;
			in_q[1] = (in_q[1] + (!in_q[0] && str[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (word_start >= str_len)
			array[i[1]++] = "\0";
		else
			array[i[1]++] = ft_substr(str, word_start, i[0] - word_start);
	}
	return (array);
}

char	**ft_split_cmds(const char *s, char *set)
{
	char	**array;
	int		nwords;
	int		in_q[2];

	in_q[0] = 0;
	in_q[1] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words(s, set, 0, 0);
	if (nwords == -1)
		return (NULL);
	array = malloc((nwords + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = ft_fill_array(array, s, set, in_q);
	array[nwords] = NULL;
	return (array);
}

// void	check_args1(char *input)
// {
// 	char **args;
// 	if (!input)
// 	{
// 		printf("exit\n");
// 		return ;
// 	}
// 	if (input[0] != '\0')
// 		add_history(input);
// 	args = ft_split_cmds(input, " ");
// 	ft_print_array(args);
// 	free(input);
// 	ft_array_free(&args);
// }

// int	main(int argc, char *argv[], char *envp[])
// {
// 	// 1. get username
// 	// 2. get home directory
// 	// 3. display prompt string and wait for input
// 	char	*prompt;
// 	char	*out;
// 	// char	**array;
// 	// int		wordcount;
// 	// char	space = ' ';
// 	(void)argc;
// 	(void)argv;

// 	out = NULL;
// 	prompt = "jdaly@minishell$ ";
// 	while (1)
// 	{
// 		out = readline(prompt);
// 		check_args1(out);

// 		// wordcount = ft_count_words(out);
// 		// printf("wordcount = %d\\n", wordcount);
// 		// array = ft_create_array(out, wordcount);
// 		// print_array(array);
// 	}
// }

// int	main(void)
// {
// 	char *str = "hello \"this is a string\"";
// 	char **args;
// 	printf("str = %s\n", str);
// 	args = ft_split_cmds(str, " ");
// 	ft_print_array(args);
// 	free(str);
// 	ft_array_free(&args);
// }