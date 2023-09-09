
# include "minishell.h"


// int main()
// {
// 	t_list *env;
// 	char *env_PATH;
// 	char **arr_paths;

// 	env = ft_env();
// 	env_PATH = get_content_by_name(env, "PATH");

// 	char line[] = "aaa:bbb:ccc:ddd";
//     char delimiter[] = ":";

// 	// arr_paths = split_string(line, delimiter);

// 	// ft_array_free(arr_paths);

// 	// printf("%s", env_PATH);
// 	// paths = split_string(env);


// 	// creating nodes
// 	int i = 0;

// 	char **array = malloc(sizeof(char *) * 5);
// 	array[0] = strdup("ls");
// 	array[1] = strdup("-la");
// 	array[2] = strdup("|");
// 	array[3] = strdup("pwd");
// 	array[4] = NULL;

// 	// Create a command list from the array
// 	t_cmdlist *cmdlist;

// 	// cmdlist = NULL;
// 	cmdlist = create_cmd_list(array, -1);

// 	// testing if builtin

// 	if (cmdlist != NULL)
// 	{
// 		// Traverse the command list and print the commands
// 		t_cmdlist *current;

// 		current = cmdlist;

// 		while (current)
// 		{
// 			t_cmd_node *node = (t_cmd_node *)current->content;
// 			char *tmp1;

// 			i = 0;
// 			while (node->cmd[i])
// 			{
// 				// tmp1 = ft_strdup( ft_find_right_path(node->cmd[i]));

// 				if (ft_is_builtin(node->cmd[i]))
// 					printf(" %s is builtin ", node->cmd[i]);

// 				if (ft_find_right_path(node->cmd[i]))
// 				{
// 					printf("right path for [%s] is: %s \n", node->cmd[i], ft_find_right_path(node->cmd[i]));
// 					// node->path = ft_find_right_path(node->cmd[i]);

// 					// free(tmp1);

// 					// printf("right path for [%s] is: %s \n", node->cmd[i], node->path);
// 					// exec_cmd(node->cmd, 0, 1);
// 				}

// 				i++;
// 			}
// 			current = current->next;
// 		}

// 		// Free the memory allocated for the command list
// 	}


// 	// ft_array_free(env);
// 	// ft_free_list(arr_paths);
// 	ft_cmdlstclear(&cmdlist, free_cmd_content);

// }
