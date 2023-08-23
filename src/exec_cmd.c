# include "minishell.h"

void	exec_cmd(char **args, int input_fd, int output_fd)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd !=STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		execvp(args[0], args);
		perror("execvp");
		exit(1);
	}
	else if (pid < 0)
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

