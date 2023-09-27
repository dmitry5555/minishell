# include "minishell.h"

// lexer analysis
// 1. split and remove whitespace
// *count words*

static int	ft_count_words(char *str)
{
	int	wordcount = 0;
	int	start = 0;
	int	i = 0;
	int	flag_sq = 0;
	int	flag_dq = 0;
	int	flag_rd = 0;

	while (str[i])
	{
		// not skipping many spaces

		if (str[i] == 39 && !flag_dq) // single
		{
			if (!flag_sq)
			{
				flag_sq = 1;
				start = i;
			}
			else
			{
				//str_copy(str, start, i)
				// printf("SQ END ++ \\n");

				wordcount++;
				flag_sq = 0;
				start = -1;
			}

		}

		if (str[i] == 34 && !flag_sq) // double
		{
			if (!flag_dq)
			{
				flag_dq = 1;
				start = i;
			}
			else
			{
				// printf("DQ END ++ \\n");
				wordcount++;
				flag_dq = 0;
				start = -1;
			}

		}

		if (str[i] && !flag_sq && !flag_dq && str[i] != 34 && str[i] != 39)
		{
			// if not space start reading
			if (!flag_rd && str[i] != ' ')
			{
				// printf("last word start\\n");
				flag_rd = 1;
				start = i;
			}
			// reach the end of word - if next one is space or quotes or EOL
			if (flag_rd && (str[i+1] == ' ' || str[i+1] == 34 || str[i+1] == 39 || !str[i+1]))
			{
				// printf("last word end\\n");
				wordcount++;
				flag_rd = 0;
			}
		}

		i++;
	}
	if (flag_dq || flag_sq)
		return (-1);
	return (wordcount);
}


static char	**ft_create_array(char *str, int wordcount)
{
	char **array;
	int	start = 0;
	int	i = 0;
	int	j = 0;
	int	flag_sq = 0;
	int	flag_dq = 0;
	int	flag_rd = 0;

	array = malloc(sizeof(char *) * (wordcount + 1));
	if (!array)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 39 && !flag_dq) // single
		{
			if (!flag_sq)
			{
				flag_sq = 1;
				start = i;
			}
			else
			{
				array[j++] = ft_strndup(&str[start], i - start + 1);
				flag_sq = 0;
				start = -1;
			}

		}

		if (str[i] == 34 && !flag_sq) // double
		{
			if (!flag_dq)
			{
				flag_dq = 1;
				start = i;
			}
			else
			{
				array[j++] = ft_strndup(&str[start], i - start + 1);
				flag_dq = 0;
				start = -1;
			}

		}

		if (str[i] && !flag_sq && !flag_dq && str[i] != 34 && str[i] != 39)
		{
			// if not space start reading
			if (!flag_rd && str[i] != ' ')
			{
				// printf("last word start\\n");
				flag_rd = 1;
				start = i;
			}
			// reach the end of word - if next one is space or quotes or EOL
			if (flag_rd && (str[i+1] == ' ' || str[i+1] == 34 || str[i+1] == 39 || !str[i+1]))
			{
				// printf("last word end\\n");
				array[j++] = ft_strndup(&str[start], i - start + 1);
				flag_rd = 0;
			}
		}
		i++;
	}
	array[j++] = NULL;
	return (array);

}

char **ft_split_cmds(char *s)
{
	char	**array;
	int		nwords;

	if (!s)
		return (NULL);
	nwords = ft_count_words(s);
	// printf("wordcount: %d\n", nwords);
	if (nwords == -1)
		return (NULL);
	// array = malloc(sizeof(char *) * (nwords + 1));
	// if (!array)
	// 	return (NULL);
	array = ft_create_array(s, nwords);
	// array[nwords] = NULL;
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
// 	args = ft_split_cmds(input);
// 	ft_print_array(args);
// 	free(input);
// 	ft_array_free(&args);
// }

// 2. create tokens

// prompt loop function
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
// 	char *str = "hello $USER";

// 	check_args1(str);
// }