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
	t_list *curr;


	flag_upd = 0;
	curr = (*env);
	while(curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			curr->content = content;
			flag_upd = 1;
		}
		// printf("%s\n",curr->name);
		curr = curr->next;
	}
	if (!flag_upd)
		ft_add_new_node_end(env, name, content); // reversed
	// check if var exist and update value
	return (0);
}

int	unset_var(t_list **env, char *name, char *content)
{
	return (0);
}

// int main()
// {
// 	t_list *env;

// 	env = ft_env(); // read current ENV
// 	// add new value
// 	set_var(&env, "USER", "valuexXX");
// 	print_list_values(env);
// }