# include "minishell.h"


void	child_process(t_cmdlist *cmd, int fd[2])
{
	t_cmd_node *node;

	node = cmd->content;

	// child redir
	if (node->in != STDIN_FILENO)
	{
		dup2(node->in, STDIN_FILENO);
		close(node->in);
	}
	if (node->out != STDOUT_FILENO)
	{
		dup2(node->out, STDOUT_FILENO);
		close(node->out);
	}
	// else if (cmd->next && dup2(fd[1], STDOUT_FILENO) == -1)
	//	return error
	close(fd[1]);

	// close read end
	close(fd[0]);

	// child_builtin
	execve(node->cmd[0], node->cmd, NULL);


}


void	exec_fork(t_cmdlist *cmd, int fd[2])
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		printf("forking error \n");
	}
	else if (!pid)
		child_process(cmd, fd);
}
void	*check_to_fork(t_cmdlist *cmd_list, int fd[2])
{
	t_cmd_node *node;

	printf("check_to_fork\n");
	node = cmd_list->content;
	if (node->in == -1 || node->out == -1)
		return NULL;
	if (node->path)
		exec_fork(cmd_list, fd);
	// close(fd[1]);
	return("");
}

void	exec_cmd(t_cmdlist *cmd_list)
{
	int fd[2];

	if (pipe(fd) == -1)
		printf("");

	check_to_fork(cmd_list, fd);

	// if(cmd->)
}

void	print_cmd_list(t_cmdlist *cmd_list)
{
	t_cmd_node *node;

	if (cmd_list != NULL)
		{
			// Traverse the command list and print the commands

			while (cmd_list) {
				node = (t_cmd_node *)cmd_list->content;
				//printf("Command: ");
				for (int i = 0; node->cmd[i] != NULL; i++) {
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

int main()
{

	char **array = malloc(sizeof(char *) * 4);
	array[0] = strdup("ls");
	array[1] = strdup("|");
	array[2] = strdup("cat");
	// array[3] = strdup("1");
	array[3] = NULL;

	// Create a command list from the array
	t_cmdlist *cmd_list;
	t_cmd_node *node;

	cmd_list = NULL;
	cmd_list = create_cmd_list(array, -1);
	ft_find_right_paths(cmd_list);
	// print_cmd_list(cmd_list);

	// execute list
	// if (cmd_list != NULL)
	{
		// Traverse the command list and print the commands
		// t_cmdlist *current = cmdlist;
		while (cmd_list) {
			node = cmd_list->content;

			for (int i = 0; node->cmd[i] != NULL; i++)
				printf("node[%d] = %s ", i, node->cmd[i]);
			// printf("\n");
			printf("Input File: %d\n", node->in);
			printf("Output File: %d\n", node->out);
			printf("---------\n");

			exec_cmd(cmd_list);
			cmd_list = cmd_list->next;
		}

		// Free the memory allocated for the command list
		ft_cmdlstclear(&cmd_list, free_cmd_content);
	}

	return 0;
}
