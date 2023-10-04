# include "minishell.h"

// print cmd list for testing
void	print_cmd_list(t_cmdlist *cmd_list)
{
	t_cmd_node *node;

	if (cmd_list != NULL)
		{
			while (cmd_list)
			{
				node = (t_cmd_node *)cmd_list->content;
				//printf("Command: ");
				for (int i = 0; node->cmd[i] != NULL; i++)
				{
					printf("cmd[%d] = %s ", i, node->cmd[i]);
				}
				printf("\n");
				printf("Input File: %d\n", node->in);
				printf("Output File: %d\n", node->out);
				printf("---------\n");

				cmd_list = cmd_list->next;
			}

			// Free the memory allocated for the command list
			ft_cmdlstclear(&cmd_list, free_cmd_content);
		}
}

void single_node(t_cmd_node *node)
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();

	if (pid!=0) // parent - accepting process
	{
		dup2(fd[1], 1);
		close(fd[0]);
		execvp(node->cmd[0], node->cmd);
		perror("execvp");
	}
	else
	{
		dup2(fd[0],0);
		close(fd[1]);
	}


}

void	run_cmds(t_cmdlist *cmd_list)
{
	t_cmd_node *node;

	// while(cmd_list)
	// {
	node = (t_cmd_node *)cmd_list->content;
	single_node(node);

	// 	cmd_list = cmd_list->next;
	// }
	perror("error");
}


void run_single(t_cmdlist *cmd_list)
{
	t_cmd_node *node1;
	t_cmd_node *node2;
	t_cmd_node *node3;

	node1 = (t_cmd_node *)cmd_list->content;
	node2 = (t_cmd_node *)cmd_list->next->content;
	// node3 = (t_cmd_node *)cmd_list->next->next->content;

	// char *arr1[] = {"ls", "ls", "-1"};
	// char *arr2[] = {"wc", "wc", "-l"};
	// char *arr3[] = {"grep", "grep", "5"};
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();

	if (pid != 0)
	{
		dup2(fd[1],1);
		close(fd[0]);
		execvp(node1->cmd[0], node1->cmd);
		// execlp("ls", "ls", "-1", NULL);
		perror("execvp");
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		execvp(node2->cmd[0], node2->cmd);
		perror("execvp");
	}

}

void	exec_all(char *out, t_list *env)
{
	char **args;
	// int		shlvl;
	t_cmdlist *cmd_list;
	t_cmd_node *node;

	cmd_list = NULL;
	// if (!out)
	// {
	// 	printf("exit\n");
	// 	return ;
	// }
	if (out[0] != '\0')
		add_history(out);

	args = ft_split_cmds(out, " "); // we get an array with cmds
	if (!args)
		ft_error(ERR_QUOTE, NULL, 2);
	if (args)
	{
		cmd_list = create_cmd_list(final_split(args, env), -1); // expand arr -> LL
		// ft_find_right_paths(cmd_list);
		// print_cmd_list(cmd_list);
		// run_cmds(cmd_list);
		// ft_cmdlstclear(&cmd_list, free_cmd_content);
		// printf("AFTER FT_SPLIT_CMDS:\n");
		// ft_print_array(args);

	}
	run_single(cmd_list);
	free(out);
}


// int	main(int argc, char *argv[], char **env)
// {
// 	t_cmd_node	*node;
// 	t_cmdlist	*current;
// 	t_list		*env_list;

// 	char		*out = NULL;
// 	// char		*shlvl;

// 	env_list = ft_env(env);
// 	// out = readline("guest@minishell $ ");

// 	while (argc && argv)
// 	// {
// 	// 	// signal(SIGINT, SIG_DFL);
// 	// 	// signal(SIGQUIT, SIG_DFL);

// 		out = readline("guest@minishell $ ");
// 		exec_all(out, env_list);
// 	}

int	main(int argc, char *argv[], char **env)
{
	t_list		*env_list;
	// t_cmd_node	*node;
	// t_cmdlist	*current;
	// t_cmdlist	*cmd_list;
	// char		*start;
	char		*out;
	// char		*shlvl;
	// cmd_list = NULL;

	// env = NULL;
	// char *out = "ls -1 | wc -l | grep src";
	env_list = ft_env(env);

	// char *arr1[] = {"ls", "ls", "-1"};
	// char *arr2[] = {"wc", "wc", "-l"};
	// char *arr3[] = {"grep", "grep", "5"};

	while (1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);

	// 	if (start)
	// 		out = readline(start);
	// 	else
			out = readline("guest@minishell $ ");
	// 	free(start);
		exec_all(out, env_list);
	// 	exec_all(out, envZ);
	}
	// ft_cmdlstclear(&cmd_list, free_cmd_content);
}