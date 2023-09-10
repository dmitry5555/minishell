
# include "minishell.h"


// int main()
// {
// 	t_list		*env;
// 	t_cmdlist 	*cmdlist;
// 	char		*env_paths;
// 	char		**arr_paths;

// 		// read currenv ENV, find 'PATH' content
// 	env = ft_env();
// 		// find node "PATH"
// 	env_paths = get_content_by_name(env, "PATH");
// 		// we have ARR with every path
// 	arr_paths = split_string(env_paths, ":");
// 		// array of commands for cmd_list, will be in s_cmdlist
// 	char **arr_cmd = malloc(sizeof(char *) * 8);
// 	arr_cmd[0] = strdup("ls");
// 	arr_cmd[1] = strdup("|");
// 	arr_cmd[2] = strdup("tree");
// 	arr_cmd[3] = strdup("|");
// 	arr_cmd[4] = strdup("echo");
// 	arr_cmd[5] = strdup("-n");
// 	arr_cmd[6] = strdup("this is a str");
// 	arr_cmd[7] = NULL;

// 	cmdlist = create_cmd_list(arr_cmd, -1);

// 	// // print cmd list   for debug
// 	// if (cmdlist != NULL)
// 	// {
// 	// 	// Traverse the command list and print the commands
// 	// 	t_cmdlist *current = cmdlist;
// 	// 	while (current != NULL) {
// 	// 		t_cmd_node *node = (t_cmd_node *)current->content;
// 	// 		//printf("Command: ");
// 	// 		for (int i = 0; node->cmd[i] != NULL; i++) {
// 	// 			printf("cmd[%d] = %s ", i, node->cmd[i]);
// 	// 		}
// 	// 		printf("\n");
// 	// 		printf("Input File: %d\n", node->in);
// 	// 		printf("Output File: %d\n", node->out);
// 	// 		printf("---------\n");

// 	// 		current = current->next;
// 	// 	}
// 	// }
// 	// else
// 	// 	printf("Failed to create the command list.\n");

// 	// find wrk path for each cmd node and save to node
// 	ft_find_right_paths(cmdlist);

// 	// run cmds
// 	if (cmdlist)
// 	{
// 		t_cmdlist *current;
// 		current = cmdlist;
// 		while (current)
// 		{
// 			t_cmd_node *node = (t_cmd_node *)current->content;

// 			if (ft_is_builtin(node->cmd[0]))
// 			{
// 				printf("🟢 MAIN @ test.c \n	starting builtin [%s] \n\n", node->cmd[0]);
// 				exec_cmd(node->cmd, 0, 1);
// 			}
// 			else if (node->path)
// 			{
// 				printf("🟢 MAIN @ test.c \n	starting cmd [%s] \n\n", node->path);
// 				exec_cmd(node->cmd, 0, 1);
// 			}
// 			else
// 				printf("🔴 MAIN @ test.c \n	not correct cmd [%s] \n\n", node->cmd[0]);
// 			current = current->next;
// 		}
// 	}

// 	ft_free_list(env);
// 	ft_free_arr(arr_paths);
// 	ft_cmdlstclear(&cmdlist, free_cmd_content);
// }
