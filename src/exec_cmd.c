# include "minishell.h"

#define FD_PIPE (-2)

void execute_cmd_list(t_cmdlist *cmd_list)
{
    int prev_fd = STDIN_FILENO; // Initialize the previous file descriptor to stdin

    while (cmd_list)
    {
        t_cmd_node *cmd_node = (t_cmd_node *)cmd_list->content;

        int fd[2] = {-1, -1}; // File descriptor array for the pipe

        // if (cmd_node->out == FD_PIPE)
        // {
        //     if (pipe(fd) == -1)
        //     {
        //         perror("pipe");
        //         exit(1);
        //     }
        // }

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0) // Child process
        {
            // Redirect input
            if (cmd_node->in != STDIN_FILENO)
            {
                dup2(cmd_node->in, STDIN_FILENO);
                close(cmd_node->in);
            }
            else if (prev_fd != STDIN_FILENO)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            // Redirect output
            if (cmd_node->out == FD_PIPE)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            else if (cmd_node->out != STDOUT_FILENO)
            {
                dup2(cmd_node->out, STDOUT_FILENO);
                close(cmd_node->out);
            }

            // Execute the command
            execvp(cmd_node->cmd[0], cmd_node->cmd);
            perror("execvp");
            exit(1);
        }
        else // Parent process
        {
            // Close the write end of the pipe if it was created
            if (cmd_node->out == FD_PIPE)
            {
                close(fd[1]);
            }

            // Wait for the child to finish
            int status;
            if (waitpid(pid, &status, 0) == -1)
            {
                perror("waitpid");
                exit(1);
            }

            // Close the read end of the previous pipe
            if (prev_fd != STDIN_FILENO)
            {
                close(prev_fd);
            }

            // Store the read end of the current pipe for the next iteration
            if (cmd_node->out == FD_PIPE)
            {
                prev_fd = fd[0];
            }
        }

        cmd_list = cmd_list->next;
    }
}



// Define a constant for the pipe file descriptor
// #define FD_PIPE (-2)

// int main()
// {
//     // Sample command list with pipe
//     // t_cmd_node cmd1 = {{"ls", "-l", NULL}, "/bin/ls", STDIN_FILENO, FD_PIPE};
//     // t_cmd_node cmd2 = {{"grep", "file.txt", NULL}, "/usr/bin/grep", FD_PIPE, STDOUT_FILENO};
//     // t_cmd_node cmd3 = {{"wc", "-l", NULL}, "/usr/bin/wc", STDIN_FILENO, STDOUT_FILENO};

//     // t_cmdlist list1 = {NULL, &cmd1};
//     // t_cmdlist list2 = {&list1, &cmd2};
//     // t_cmdlist list3 = {&list2, &cmd3};

//     // Run the command list

// 	char **array = malloc(sizeof(char *) * 4);
//     array[0] = strdup("1");
//     array[1] = strdup("<");
//     array[2] = strdup("ls");
// 	// array[3] = strdup("1");
//     // array[4] = strdup("1");
//     array[3] = NULL;

// 	t_cmdlist *cmd_list = create_cmd_list(array, -1);
// 	// ft_find_right_paths(cmd_list);
//     // execute_cmd_list(cmd_list);

//     return 0;
// }


// void child_process(node)
// {
	
// }

// void	exec_fork(t_cmd_node *node)
// {
// 	int pid;
// 	int fd[2];

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(fd[0] , STDOUT_FILENO);
// 		close(fd[0]);
// 		execvp(args[0], args);
// 	// 	perror("execvp");
// 	}

// 	// if (pid == 0) // child process
// 	// {
// 	// 	if (input_fd != STDIN_FILENO) // if input was changed from default STDIN
// 	// 	{
// 	// 		dup2(input_fd, STDIN_FILENO);
// 	// 		close(input_fd);
// 	// 	}
// 	// 	if (output_fd !=STDOUT_FILENO) // if output was changed from default STDOUT
// 	// 	{
// 	// 		dup2(output_fd, STDOUT_FILENO);
// 	// 		close(output_fd);
// 	// 	}
// 	// 	execvp(args[0], args);
// 	// 	perror("execvp");
// 	// 	exit(1);
// 	// }
// }


// int exec_all(t_cmdlist *cmd_list)
// {
// 	t_cmd_node	*node;
// 	t_cmdlist	*current;

// 	if (cmd_list)
// 	{
// 		current = cmd_list;
// 		while (current)
// 		{
// 			node = (t_cmd_node *)current->content;
// 			exec_fork(node);
// 			current = current->next;
// 		}
// 	}
// 	return(0);
// }


// int main()
// {
// 	char **array = malloc(sizeof(char *) * 4);
//     array[0] = strdup("echo");
//     array[1] = strdup("|");
//     array[2] = strdup("grep");
//     array[3] = NULL;

//     // Create a command list from the array
// 	t_cmdlist *cmd_list = create_cmd_list(array, -1);
// 	ft_find_right_paths(cmd_list);
// 	// cmd_list = NULL;
// 	// cmd_list = create_cmd_list(array, -1);


// }

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


int ft_execute(t_cmd_node *node)
{
	//overwrite ; or | or NULL with NULL to use the array as input for execve.
	//we are here in the child so it has no impact in the parent process.
	dup2(node->in, STDIN_FILENO);
	close(node->in);
	execve(node->cmd[0], node->cmd, NULL);
	perror("execve");
	return EXIT_FAILURE;
	// execve(cmd[0], argv, env);
	// printf("cannot execute ");
	// return(0);
}

int main()
{
	int fd[2];

   	char **array = malloc(sizeof(char *) * 4);
    array[0] = strdup("cat");
    array[1] = strdup("1");
    array[1] = strdup(">");
    array[2] = strdup("2");
    array[3] = NULL;

    // Create a command list from the array
	t_cmdlist *cmdlist;
	t_cmd_node *node;
	
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
            node = (t_cmd_node *)current->content;
            // if ( fork() == 0)
			// {
			// 	if (ft_execute(node))
			// 		return (1);
			// }
            
			pipe(fd);
			if (fork() == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				if (ft_execute(node))
					return (1);
			}
			else
			{
				close(fd[1]);
				close(node->in);
				node->in = fd[0];
			}
			current = current->next;
        }

        // Free the memory allocated for the command list
        ft_cmdlstclear(&cmdlist, free_cmd_content);
    }


    return 0;
}
