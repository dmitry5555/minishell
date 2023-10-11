# include "minishell.h"

// sets a var, env
// UNSET - unsets a var (need to check first, last cases)
// EXPORT (local to env)
// ENV


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
			// curr->is_env = is_env;
			flag_upd = 1;
		}
		curr = curr->next;
	}
	if (!flag_upd)
		ft_add_new_node_start(env, name, content); // reversed
	return (0);
}

void unset_var(t_list **env, char *name)
{
	t_list	*curr;

	curr = (*env);
	while(curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			curr->name = NULL;
			curr->content = NULL;
		}
		curr = curr->next;
	}
}

// void unset_var(t_list **env, char *name)
// {
// 	t_list *temp;
// 	t_list *current = *env;  // Initialize current to the head of the list

// 	if (current == NULL) {
// 		return;
// 	}

// 	// Handle the case where the first node needs to be removed
// 	if (!ft_strcmp(current->name, name))
// 	{
// 		*env = (*env)->next;
// 		free(current->name);
// 		free(current->content);
// 		free(current);
// 		return;
// 	}

// 	// Traverse the linked list to find the node before the one to be removed
// 	while (current->next != NULL && ft_strcmp(current->next->name, name))
// 	{
// 		current = current->next;
// 	}

// 	// If the value was not found in the linked list
// 	if (current->next == NULL) {
// 		return;
// 	}

// 	temp = current->next;
// 	current->next = temp->next;
// 	free(temp->name);
// 	free(temp->content);
// 	free(temp);
// }


// int	unset_var(t_list **env, char *name)
// {
// 	t_list	*curr;
// 	t_list	*prev;

// 	curr = NULL;
// 	prev = NULL;
// 	curr = (*env);
// 	while(curr)
// 	{
// 		if (!ft_strcmp(curr->name, name))
// 		{
// 			// printf("unsetting❌\n");
// 			if (curr->next)
// 				prev->next = curr->next;
// 			// free(curr->name);
// 			// free(curr->content);
// 			// free(curr);
// 			return (0);
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// 	return (0);
// }

// int main()
// {
// 	t_list *env;
// 	t_list *current;

// 	env = ft_env();

// 	// IS VISIBLE
// 	set_var(&env, "VAR_X", "HEAP SUMMARY", 1);
// 	// IS SESSION, EMPTY
// 	set_var(&env, "VAR_Z", "", 0);
// 	unset_var(&env, "VAR_X");

// 	current = env;
// 	// print loop
// 	while (current != NULL) {
// 		printf("%s\n", current->name);
// 		printf("%s\n", current->content);
// 		current = current->next;
// 	}

// 	ft_cleanup(&env);
// }