# include "minishell.h"


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

// 	// array of commands for cmd_list, will be in s_cmdlist
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
// 		int i;
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
// 				{
// 					printf("🟢 MAIN @ test.c \n	[%s]is builtin, can run \n\n", node->cmd[i]);
// 					exec_cmd(node->cmd, 0, 1);
// 				}
// 				else if (ft_find_right_path(node->cmd[i], node->path))
// 				{
// 					printf("❌ MAIN @ test.c \n	exit in return 1 \n\n");
// 					// return(0);
// 				}
// 				exec_cmd(node->cmd, 0, 1);

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