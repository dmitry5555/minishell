# include "minishell.h"

void	exec_cmd(char **args, int input_fd, int output_fd)
{
	int pid;

	pid = fork();
	if (pid == 0) // child process
	{
		if (input_fd != STDIN_FILENO) // if input was changed from default STDIN
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd !=STDOUT_FILENO) // if output was changed from default STDOUT
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		execvp(args[0], args);
		perror("execvp");
		exit(1);
	}
	else if (pid < 0) // parent process
	{
		perror("fork");
		exit(1);
	}
}


// int main(int ac, char **av)
// {
// 	int	file2;
// 	int	pipe_fd[2];
// 	(void)ac;

// 	pipe(pipe_fd);
// 	//pipe_fd[1] input
// 	//pipe_fd[0] output

//     char *cmd1[] = {"ls", "-f", NULL};
//     char *cmd2[] = {"grep", ".DS_Store", NULL};

// 	file2 = open("test2", O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 	// while (cmd, flags)
// 	// <<
// 	exec_cmd(cmd1, STDIN_FILENO, pipe_fd[1]);
// 	close(pipe_fd[1]);

// 	exec_cmd(cmd2, pipe_fd[0], file2);
// 	close(pipe_fd[0]);

// 	close(file2);

// }


// int main()
// {
//     char **array = malloc(sizeof(char *) * 4);
//     array[0] = strdup("echo");
//     array[1] = strdup("|");
//     array[2] = strdup("grep");
//     array[3] = NULL;

//     // Create a command list from the array
// 	t_cmdlist *cmdlist;

// 	cmdlist = NULL;
// 	cmdlist = create_cmd_list(array, -1);

//     //Check if the command list was created successfully
//     if (cmdlist != NULL)
// 	{
//         // Traverse the command list and print the commands
//         t_cmdlist *current = cmdlist;
//         while (current != NULL) {
//             t_cmd_node *node = (t_cmd_node *)current->content;
//             //printf("Command: ");
//             for (int i = 0; node->cmd[i] != NULL; i++) {
//                 printf("cmd[%d] = %s ", i, node->cmd[i]);
//             }
//             printf("\n");
//             printf("Input File: %d\n", node->in);
//             printf("Output File: %d\n", node->out);
//             printf("---------\n");

//             current = current->next;
//         }

//         // Free the memory allocated for the command list
//         ft_cmdlstclear(&cmdlist, free_cmd_content);
//     }
// 	else
// 	{
//         printf("Failed to create the command list.\n");
//     }

//     return 0;
// }
