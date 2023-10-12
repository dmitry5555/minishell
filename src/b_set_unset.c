#include "minishell.h"

int	set_var(t_list **env, char *name, char *content)
{
	int		flag_upd;
	t_list	*curr;

	curr = NULL;
	flag_upd = 0;
	curr = (*env);
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			if (curr->content)
				free(curr->content);
			curr->content = ft_strdup(content);
			// curr->is_env = is_env;
			flag_upd = 1;
		}
		curr = curr->next;
	}
	if (!flag_upd)
		ft_add_new_node_end(env, name, content);
	return (0);
}

void	unset_var(t_list **env, char *name)
{
	t_list	*curr;

	curr = (*env);
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			curr->name = NULL;
			curr->content = NULL;
		}
		curr = curr->next;
	}
}