# include "minishell.h"

// adds new var without checking if it exist
// int set_var(t_list **env, char *name, char *content)
// {
// 	ft_add_new_node_end(env, name, content);
// 	// check if var exist and update value
// 	return (0);
// }

int set_var(t_list **env, char *name, char *content)
{
	int		flag_upd;
	t_list	*curr;

	curr = NULL;
	flag_upd = 0;
	// curr = NULL;
	// curr = malloc(sizeof(t_list));

	curr = (*env);
	while(curr)
	{
		if (!ft_strcmp(curr->name, name)) // name exists
		{
			if (curr->content)
				free(curr->content);
			curr->content = ft_strdup(content);
			flag_upd = 1;
		}
		// printf("%s\n",curr->name);
		curr = curr->next;
	}
	if (!flag_upd)
	{
		printf("adding new var 🔥\n");
		ft_add_new_node_start(env, name, content); // reversed
	}
	return (0);
}

int	unset_var(t_list **env, char *name, char *content)
{
	return (0);
}

int main()
{
	t_list *env;

	env = ft_env(); // read current ENV
	// add new value
	set_var(env, "USERSSSS", "valuexXASDASDX");
	print_list_values(env);
	// free(env);
}