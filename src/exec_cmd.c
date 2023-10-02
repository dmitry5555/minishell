# include "minishell.h"

extern int g_status;

static void *child_redir(t_cmdlist *cmd, int fd[2], t_list *env)
{
	t_cmd_node *node;

	node = cmd->content;
	if (node->in != STDIN_FILENO)
	{
		dup2(node->in, STDIN_FILENO);
		close(node->in);
	}
	if (node->out != STDOUT_FILENO)
	{
		dup2(node->out, STDOUT_FILENO); // now node->out is STDOUT
		close(node->out); // we close (free) node->out
	}
	else if (cmd->next && dup2(fd[1], STDOUT_FILENO) == -1)
		printf("error dup2\n");
	close(fd[1]);
	return("");
}

void	*child_builtin(t_cmdlist *cmd, int fd[2], t_list *env)
{
	t_cmd_node *node;
	node = cmd->content;
	// printf("cmd+path: %s \n", node->path);
	// printf("in: %d \n", node->in);
	// printf("out: %d \n", node->out);
	execve(node->path, node->cmd, NULL);
	return("");
}

// void	free_content(void *content)
// {
// 	t_cmd_node	*node;

// 	node = content;

// 	// ft_free_matrix(&node->full_cmd);
// 	free(node->path);
// 	if (node->in != STDIN_FILENO)
// 		close(node->in);
// 	if (node->out != STDOUT_FILENO)
// 		close(node->out);
// 	free(node);
// }


void	*child_process(t_cmdlist *cmd, int fd[2], t_list *env)
{
	t_cmd_node *node;
	node = cmd->content;

	child_redir(cmd, fd, env);
	close(fd[0]);
	child_builtin(cmd, fd, env);

	// free_cmd_content(node);
	// if (node->in != STDIN_FILENO)
	// 	close(node->in);
	// if (node->out != STDOUT_FILENO)
	// 	close(node->out);
	return("");
}


void	exec_fork(t_cmdlist *cmd, int fd[2], t_list *env)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		printf("forking error \n");
	}
	else if (!pid) // child process
		child_process(cmd, fd, env);
}

void	*check_to_fork(t_cmdlist *cmd_list, int fd[2], t_list *env)
{
	t_cmd_node *node;

	// node = cmd_list->content;
	// if (node->in == -1 || node->out == -1)
	// 	return NULL;
	// // printf("cd\n");
	// // printf("%s\n", node->cmd[0]);

	// if (!ft_strcmp("cd", node->cmd[0]))
	// 	ft_cd(node, env);
	// else if (!ft_strcmp("env", node->cmd[0]))
	// 	ft_env(env);
	// else if (!ft_strcmp("pwd", node->cmd[0]))
	// 	ft_pwd();
	// else if (node->path)
	// 	exec_fork(cmd_list, fd, env);
	return("");
}

void	exec_cmd(t_cmdlist *cmd_list, t_list *env)
{
	int fd[2];

	if (pipe(fd) == -1)
		printf("");
	check_to_fork(cmd_list, fd, env);
	close(fd[1]);
	if(cmd_list->next && !((t_cmd_node *)cmd_list->next->content)->in)
		((t_cmd_node *)cmd_list->next->content)->in = fd[0];
	else
		close(fd[0]);
	// if smth wrong with pipes
	// if (((t_cmd_node *)cmd_list->content)->in > 2)
	// 	close(((t_cmd_node *)cmd_list->content)->in);
	// if (((t_cmd_node *)cmd_list->content)->out > 2)
	// 	close(((t_cmd_node *)cmd_list->content)->out);
}

// print cmd list for testing
void	print_cmd_list(t_cmdlist *cmd_list)
{
	t_cmd_node *node;

	if (cmd_list != NULL)
		{
			while (cmd_list) {
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

// main for testing pipes
// int main()
// {

// 	char **array = malloc(sizeof(char *) * 7);
// 	array[0] = strdup("ls");
// 	array[1] = strdup("-lf");
// 	array[2] = strdup("|");
// 	array[3] = strdup("cat");
// 	array[4] = strdup(">");
// 	array[5] = strdup("1");
// 	array[6] = NULL;

// 	// Create a command list from the array
// 	t_cmdlist *cmd_list;
// 	t_cmd_node *node;

// 	cmd_list = NULL;
// 	cmd_list = create_cmd_list(array, -1);
// 	ft_find_right_paths(cmd_list);
// 	// print_cmd_list(cmd_list);

// 	// execute list
// 	// if (cmd_list != NULL)
// 	{
// 		// Traverse the command list and print the commands
// 		// t_cmdlist *current = cmdlist;
// 		while (cmd_list) {
// 			node = cmd_list->content;

// 			// for (int i = 0; node->cmd[i] != NULL; i++)
// 			// 	printf("node[%d] = %s ", i, node->cmd[i]);
// 			// // printf("\n");
// 			// printf("Input File: %d\n", node->in);
// 			// printf("Output File: %d\n", node->out);
// 			// printf("---------\n");

// 			exec_cmd(cmd_list);
// 			cmd_list = cmd_list->next;
// 		}

// 		// Free the memory allocated for the command list
// 		ft_cmdlstclear(&cmd_list, free_cmd_content);
// 	}

// 	return 0;
// }

void	sig_hand(int sig)
{
	if (sig == SIGINT)
	{
		printf("ign sign = ctrl_c\n");
		g_status = SIGINT;
	}
	if (sig == SIGQUIT)
	{
		printf("quit sign = ctrl+|\n");

	}
}

// // main for testing signals
// int	main(int argc, char **argv)
// {

// 	while (argv && argc)
// 	{
// 		// signal(SIGINT, sig_hand);
// 		if (g_status == SIGINT)
// 		{
// 			signal(SIGINT, SIG_DFL);
// 		}
// 		else
// 		{
// 			signal(SIGINT, sig_hand);
// 			signal(SIGQUIT, sig_hand);
// 		}


// 	}

// 	return 0;
// }