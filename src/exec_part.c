# include "minishell.h"

int g_status;


// change shlvl on new minishell / exit
void change_shlvl(t_list *env, int inc)
{
	char *shlvl;

	while(env)
	{
		if (!ft_strcmp(env->name, "SHLVL"))
		{
			env->content = ft_itoa(ft_atoi(env->content) + 1);
			// set_var(&env, "SHLVL", "2");
		}
		env = env->next;
	}
}

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
			// ft_cmdlstclear(&cmd_list, free_cmd_content);
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

void	*run_single(t_cmdlist *cmd_list, int fd[2], t_list *env)
{
	t_cmd_node *node;
	pid_t pid;

	node = (t_cmd_node *)cmd_list->content;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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

		execve(node->path, node->cmd, NULL); //change env to array
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

int	run_multiple(t_cmdlist *cmd_list, t_list *env)
{
	int fd[2];
	while (cmd_list)
	{
		if(0)
		{}
		if (ft_strcmp( ((t_cmd_node *)cmd_list->content)->cmd[0], "cd") == 0)
			ft_cd(((t_cmd_node *)cmd_list->content), env);
		else if (ft_strcmp( ((t_cmd_node *)cmd_list->content)->cmd[0], "echo") == 0)
			ft_echo( ((t_cmd_node *)cmd_list->content)->cmd );
		else if (ft_strcmp( ((t_cmd_node *)cmd_list->content)->cmd[0], "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp( ((t_cmd_node *)cmd_list->content)->cmd[0], "env") == 0)
			ft_print_env(env);
		else if (ft_strcmp( ((t_cmd_node *)cmd_list->content)->cmd[0], "export") == 0)
			ft_export((t_cmd_node *)cmd_list->content, env);
		else if (ft_strcmp( ((t_cmd_node *)cmd_list->content)->cmd[0], "unset") == 0)
			ft_unset(((t_cmd_node *)cmd_list->content)->cmd[1], env);	
		else
		{
			pipe(fd);
			// if (ft_strcmp( ((t_cmd_node *)cmd_list->content)->cmd[0], "./minishell") == 0)
			// 	change_shlvl(env, )
			run_single(cmd_list, fd, env);

			close(fd[WRITE_END]);
			if (cmd_list->next && !((t_cmd_node *)cmd_list->next->content)->in)
				((t_cmd_node *)cmd_list->next->content)->in = fd[READ_END];
			else
				close(fd[READ_END]);
		}
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
		ft_find_right_paths(cmd_list);
		i = ft_cmdlstsize(cmd_list);
		g_status = run_multiple(cmd_list, env);
		while (i-- > 0)
			waitpid(-1, &g_status, 0);
		// print_cmd_list(cmd_list);
		ft_cmdlstclear(&cmd_list, free_cmd_content);
		return (1);
	}
	return (1);
}

int	main(int argc, char *argv[], char **env)
{
	t_list		*env_list;
	char		*out;
	env_list = ft_env(env);

	while (1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		out = readline("guest@minishell $ ");
		exec_all(out, env_list);
	}
}