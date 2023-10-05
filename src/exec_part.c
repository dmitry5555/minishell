# include "minishell.h"

int g_status;

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

void	*run_single(t_cmdlist *cmd_list, int fd[2])
{
	t_cmd_node *node;

	node = (t_cmd_node *)cmd_list->content;
	// node2 = (t_cmd_node *)cmd_list->next->content;
	// node3 = (t_cmd_node *)cmd_list->next->next->content;

	// char *arr1[] = {"ls", "ls", "-1"};
	// char *arr2[] = {"wc", "wc", "-l"};
	// char *arr3[] = {"grep", "grep", "5"};

		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		
		pid_t pid;
		if (node->in == -1 || node->out == -1)
			return (NULL);
		pid = fork();

		if (pid == -1) //error
		{
			close(fd[READ_END]);
			close(fd[WRITE_END]);
			ft_error(ERR_FORK, NULL, 1);
		}
		else if (pid == 0) //child
		{
			if (node->in != STDIN_FILENO)
			{
				if (dup2(node->in, STDIN_FILENO) == -1)
					return (ft_error(ERR_DUP, NULL, 1));
				close(node->in);
			}
			if (node->out != STDOUT_FILENO)
			{
				if (dup2(node->out, STDOUT_FILENO) == -1)
					return (ft_error(ERR_DUP, NULL, 1));
				close(node->out);
			}
			else if (cmd_list->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
				return (ft_error(ERR_DUP, NULL, 1));
			close(fd[WRITE_END]);
			close(fd[READ_END]);
		
			execvp(node->cmd[0], node->cmd);
			// ft_cmdlstclear(&cmd_list, free_cmd_content);
			// exit(g_status);
			// execlp("ls", "ls", "-1", NULL);
		}
		else //parent
		{
			// dup2(fd[0], 0);
			
			// execvp(node2->cmd[0], node2->cmd);
			// perror("execve");
		}
	return (cmd_list);
}

int	run_multiple(t_cmdlist *cmd_list)
{
	int fd[2];
	// pipe(fd);
	while (cmd_list)
	{
		pipe(fd);
		run_single(cmd_list, fd);
		close(fd[WRITE_END]);
		if (cmd_list->next && !((t_cmd_node *)cmd_list->next->content)->in)
			((t_cmd_node *)cmd_list->next->content)->in = fd[READ_END];
		else
			close(fd[READ_END]);
		cmd_list = cmd_list->next;
	}
	return (g_status);
}

int	exec_all(char *out, t_list *env)
{
	int	i;
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
	free(out);
	if (!args)
		ft_error(ERR_QUOTE, NULL, 2);
	if (args)
	{
		cmd_list = create_cmd_list(final_split(args, env), -1); // expand arr -> LL
		if (!cmd_list)
			return (1);
		i = ft_cmdlstsize(cmd_list);
		g_status = run_multiple(cmd_list);
		while (i-- > 0)
			waitpid(-1, &g_status, 0);
		// ft_find_right_paths(cmd_list);
		// print_cmd_list(cmd_list);
		// run_cmds(cmd_list);
		// ft_cmdlstclear(&cmd_list, free_cmd_content);
		// printf("AFTER FT_SPLIT_CMDS:\n");
		// ft_print_array(args);
		return (1);

	}
	return (1);
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


		out = readline("guest@minishell $ ");
		exec_all(out, env_list);

	}
	// ft_cmdlstclear(&cmd_list, free_cmd_content);
}