# include "minishell.h"

char *get_content_by_name(t_list *head, const char *name)
{
	t_list *current = head;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			return current->content;
		}
		current = current->next;
	}

	// Node with the specified name not found
	return NULL;
}



// int main()
// {
// 	t_list		*env;
// 	t_cmdlist 	*cmd_list;
// 	char		*env_paths;
// 	char		**arr_paths;

// 	// read currenv ENV, find 'PATH' content
// 	env = ft_env();
// 	env_paths = get_content_by_name(env, "PATH");

// 	// we have ARR with every path
// 	arr_paths = split_string(env_paths, ":");


// 	char **arr_cmd = malloc(sizeof(char *) * 7);
// 	arr_cmd[0] = strdup("ls");
// 	arr_cmd[1] = strdup("-la");
// 	arr_cmd[2] = strdup("|");
// 	arr_cmd[3] = strdup("pwd");
// 	arr_cmd[4] = strdup("grep");
// 	arr_cmd[5] = strdup("cd");
// 	arr_cmd[6] = NULL;

// 	cmd_list = create_cmd_list(arr_cmd, -1);

// 	if (cmd_list)
// 	{
// 		// Traverse the command list and print the commands
// 		t_cmdlist *current;
// 		int i = 0;
// 		current = cmd_list;

// 		while (current)
// 		{
// 			t_cmd_node *node = (t_cmd_node *)current->content;
// 			char *tmp1;

// 			i = 0;
// 			while (node->cmd[i])
// 			{
// 				// tmp1 = ft_strdup( ft_find_right_path(node->cmd[i]));

// 				if (ft_is_builtin(node->cmd[i]))
// 					printf("MAIN @ test.c \n	[%s]is builtin, can run \n\n", node->cmd[i]);

// 				if (ft_find_right_path(node->cmd[i]))
// 				{
// 					printf("right path for [%s] is: %s \n", node->cmd[i], ft_find_right_path(node->cmd[i]));
// 					node->path = ft_find_right_path(node->cmd[i]);

// 					// free(tmp1);

// 					printf("right path for [%s] is: %s \n", node->cmd[i], node->path);
// 					// exec_cmd(node->cmd, 0, 1);
// 				}

// 				i++;
// 			}
// 			current = current->next;
// 		}

// 		// Free the memory allocated for the command list
// 	}

// 	ft_free_list(env);
// 	ft_free_arr(arr_paths);
// 	// ft_array_free(arr_cmd);
// 	ft_cmdlstclear(&cmd_list, free_cmd_content);


// }