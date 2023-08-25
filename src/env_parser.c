# include "minishell.h"

// parse env to have a local copy

// split single ENV string
char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*equal_sign_pos;

	// equal_sign_pos =
	equal_sign_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof(tmp)*(2+1));
	tmp[0] = ft_substr(arg, 0, equal_sign_pos - arg);
	tmp[1] = ft_substr(equal_sign_pos, 1, ft_strlen(arg));
	tmp[2] = NULL;
	return(tmp);
}

void print_list_values(const t_list *list)
{
	const t_list *current = list;

	while (current != NULL) {
		printf("%s\n", current->name);
		printf("%s\n", current->content);
		current = current->next;
	}
}

// parse ENV to linked list
t_list *parse_env()
{
	char	**env_lines;
	char	**temp;
	t_list	*env;

	env_lines = environ;
	while (*env_lines)
	{
		temp = get_key_value_pair(*env_lines);
		// printf("var: %s\n", temp[0]);
		// printf("val: %s\n", temp[1]);
		ft_add_new_node_end(&env, temp[0], temp[1]);

		free(temp[0]);
		free(temp[1]);
		free(temp);

		env_lines++;

	}
	return(env);
	// testing
}

// int	main()
// {
// 	t_list	*curr_env;

// 	curr_env = parse_env();
// 	print_list_values(curr_env);
// }