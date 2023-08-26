# include "minishell.h"

int set_var(t_list **env, char *name, char *content)
{
	int		flag_upd;
	t_list	*curr;

	curr = NULL;
	flag_upd = 0;


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
		curr = curr->next;
	}
	if (!flag_upd)
	{
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
	t_list *current;

	env = ft_env();
	set_var(&env, "VAR_X", "HEAP SUMMARY");

	current = env;
	while (current != NULL) {
		printf("%s\n", current->name);
		printf("%s\n", current->content);
		current = current->next;
	}

	ft_cleanup(&env);
}