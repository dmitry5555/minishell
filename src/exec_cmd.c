# include "minishell.h"


void	child_process(t_cmd_node *cmd, int fd[2])
{
	if (cmd->in != STDIN_FILENO)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != STDOUT_FILENO)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	close(fd[1]);
	execvp(cmd->cmd[0], cmd->cmd);
	perror("execvp");
}


void	exec_fork(t_cmd_node *cmd, int fd[2])
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		printf("forking error \n");
	}
	else if (pid == 0)
		child_process(cmd, fd);
}
void	*check_to_fork(t_cmd_node *cmd, int fd[2])
{
	if (cmd->path)
		exec_fork(cmd, fd);
}

void	exec_cmd(t_cmd_node *cmd)
{
	int fd[2];

	pipe(fd);
	exec_fork(cmd, fd);
}

int main()
{

	char **array = malloc(sizeof(char *) * 5);
	array[0] = strdup("cat");
	array[1] = strdup("1");
	array[2] = strdup(">");
	array[3] = strdup("2");
	array[4] = NULL;

	// Create a command list from the array
	t_cmdlist *cmdlist;
	t_cmd_node *cmd;

	cmdlist = NULL;
	cmdlist = create_cmd_list(array, -1);
	ft_find_right_paths(cmdlist);

	// Check / print  the command
	// if (cmdlist != NULL)
	// {
	//     // Traverse the command list and print the commands
	//     t_cmdlist *current = cmdlist;
	//     while (current != NULL) {
	//         f *node = (t_cmd_node *)current->content;
	//         //printf("Command: ");
	//         for (int i = 0; node->cmd[i] != NULL; i++) {
	//             printf("cmd[%d] = %s ", i, node->cmd[i]);
	//         }
	//         printf("\n");
	//         printf("Input File: %d\n", node->in);
	//         printf("Output File: %d\n", node->out);
	//         printf("---------\n");

	//         current = current->next;
	//     }

	//     // Free the memory allocated for the command list
	//     ft_cmdlstclear(&cmdlist, free_cmd_content);
	// }

	// execute list
	if (cmdlist != NULL)
	{
		// Traverse the command list and print the commands
		t_cmdlist *current = cmdlist;
		while (current != NULL) {
			cmd = current->content;

			exec_cmd(cmd);

			current = current->next;
		}

		// Free the memory allocated for the command list
		ft_cmdlstclear(&cmdlist, free_cmd_content);
	}

	return 0;
}
