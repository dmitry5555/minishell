
# include "minishell.h"

void print_cmd_list(t_cmdlist *cmd_list) {
    t_cmdlist *current = cmd_list;
    int index = 0;

    while (current) {
        t_cmd_node *node = (t_cmd_node *)current->content;

        printf("Command %d:\n", index);
        printf("Path: %s\n", node->path);

        printf("Arguments:\n");
        for (int i = 0; node->cmd[i] != NULL; i++) {
            printf("  %d: %s\n", i, node->cmd[i]);
        }

        current = current->next;
        index++;
    }
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

// 	// array of commands for cmd_list, will be in s_cmdlist
// 	char **arr_cmd = malloc(sizeof(char *) * 7);

// 	arr_cmd[0] = strdup("ls");
// 	arr_cmd[1] = strdup("cd");
// 	arr_cmd[2] = strdup("tree");
// 	arr_cmd[3] = strdup("cat");
// 	arr_cmd[4] = strdup("grep");
// 	arr_cmd[5] = strdup("ls");
// 	arr_cmd[6] = NULL;

// 	cmd_list = create_cmd_list(arr_cmd, -1);

// 	print_cmd_list(cmd_list);

// 	// ft_find_right_paths(cmd_list);

// 	// if (cmd_list)
// 	// {
// 	// 	t_cmdlist *current;
// 	// 	int i;
// 	// 	current = cmd_list;

// 	// 	while (current)
// 	// 	{
// 	// 		t_cmd_node *node = (t_cmd_node *)current->content;
// 	// 		// char *tmp1;

// 	// 		// i = 0;
// 	// 		// while (node->cmd[i])
// 	// 		// {
// 	// 			// tmp1 = ft_strdup( ft_find_right_path(node->cmd[i]));
// 	// 			if (ft_is_builtin(node->cmd[0]))
// 	// 			{
// 	// 				printf("🟢 MAIN @ test.c \n	starting builtin [%s] \n\n", node->cmd[i]);
// 	// 				exec_cmd(node->cmd, 0, 1);
// 	// 			}
// 	// 			else if (node->path)
// 	// 			{
// 	// 				printf("🟢 MAIN @ test.c \n	starting cmd [%s] \n\n", node->path);
// 	// 				exec_cmd(node->cmd, 0, 1);
// 	// 			}
// 	// 			else
// 	// 			{
// 	// 				printf("🟢 MAIN @ test.c \n	not correct cmd [%s] \n\n", node->cmd[i]);
// 	// 			}
// 	// 		// 	i++;
// 	// 		// }

// 	// 			// if (ft_is_builtin(node->cmd[i]))
// 	// 			// {
// 	// 			// 	printf("🟢 MAIN @ test.c \n	starting builtin [%s] \n\n", node->cmd[i]);
// 	// 			// 	exec_cmd(node->cmd, 0, 1);
// 	// 			// }
// 	// 			// // if have path = cmd is correct
// 	// 			// else if ()
// 	// 			// {
// 	// 			// 	printf("🟢 MAIN @ test.c \n	startin cmd from ft_find_right_path [%s] \n\n", node->cmd[i]);
// 	// 			// 	// return(0);
// 	// 			// }

// 	// 			current = current->next;
// 	// 	}
// 	// }

// 		// Free the memory allocated for the command list

// 	ft_free_list(env);
// 	ft_free_arr(arr_paths);
// 	// ft_array_free(arr_cmd);
// 	ft_cmdlstclear(&cmd_list, free_cmd_content);


// }




// OLD MAIN

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
