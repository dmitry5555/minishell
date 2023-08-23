// diff types of pipes (diff. mains)

# include "minishell.h"

// int main() {
// 	int pipefd[2];

// 	int fd1;
// 	int fd2;
// 	int pid;
// 	int i;
// 	// int status;
// 	char *const ls_args[] = {"ls", "-l", "-a", NULL}; // Command and arguments for ls
// 	char *const env[] = {NULL};
// 	// ssize_t bytes_read;

// 	// char buffer[MAX_BUFFER_SIZE];

// 	fd1 = open("test1", O_RDONLY);
// 	fd2 = open("test2", O_WRONLY | O_CREAT | O_TRUNC, 0666);

// 	pipe(pipefd);

// 	i = 3;
// 	while(i--)
// 	{
// 		// pipe(pipefd);
// 		pid = fork();

// 		if (pid == 0) // child process
// 		{

// 			dup2(fd1,STDIN_FILENO); // STDIN taken from file 1
// 			dup2(pipefd[1],STDOUT_FILENO); // STDOUT goes to pipe INPUT
// 			// close(pipefd[0]);
// 			// close(fd1);

// 			// while ((bytes_read = read(fd1, buffer, sizeof(buffer))) > 0)
// 			//     write(STDOUT_FILENO, buffer, bytes_read);

// 			// close(pipefd);

// 			execve("/bin/ls", ls_args, env);
// 			perror("execve");

// 			return EXIT_FAILURE;

// 			// exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			// waitpid(-1, &status, 0);

// 			dup2(fd2, STDOUT_FILENO); // output to file 2
// 			// dup2(pipefd[0], STDIN_FILENO); // get input from pipe

// 			close(pipefd[1]);
// 			close(fd2);

// 			wait(NULL);
// 			// exit(EXIT_FAILURE);
// 			// printf("finished waiting ✅ %d \n", getpid());
// 		}
// 		// i++;
// 	}

// 	close(fd2);
// 	return 0;
// }

// int main(int ac, char **av)
// {
// 	char *const ls_args[] = {"ls", "-l", "-a", NULL}; // Command and arguments for ls
// 	char *const env[] = {NULL};
// 	execve("/bin/ls", ls_args, env);
// 	perror("execve");
// 	return EXIT_FAILURE;
// }


// int main(int ac, char **av) {
// 	int pipefd[2];
// 	int fd1, fd2;
// 	int pid;
// 	int i;
// 	// int status;
// 	ssize_t bytes_read;

// 	char buffer[MAX_BUFFER_SIZE];

// 	fd1 = open("test1", O_RDONLY);
// 	fd2 = open("test2", O_WRONLY | O_CREAT | O_TRUNC, 0666);

// 	pipe(pipefd);

// 	i = 2;
// 	while (i--) {
// 		pid = fork();

// 		if (pid == 0)
// 		{ // child process
// 			close(pipefd[0]); // Close unused read end of the pipe

// 			// dup2(pipefd[1], STDOUT_FILENO);
// 			while ((bytes_read = read(fd1, buffer, sizeof(buffer))) > 0)
// 				write(STDOUT_FILENO, buffer, bytes_read); // Write to the pipe

// 			close(pipefd[1]);
// 			// close(fd1);
// 			return EXIT_SUCCESS; // Return success to indicate child completion
// 		}
// 		else
// 		{ // parent
// 			close(pipefd[1]);
// 			dup2(fd2, STDOUT_FILENO);
// 			wait(NULL);
// 		}
// 	}

// 	close(pipefd[1]); // Close write end of the pipe in the parent

// 	// while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0)
// 	//     write(fd2, buffer, bytes_read); // Write to the output file

// 	close(pipefd[0]);
// 	close(fd1);
// 	close(fd2);

// 	// Wait for all child processes


// 	return EXIT_SUCCESS;
// }



// int main(int ac, char **av) {
// 	int pipefd[2];
// 	// int fd1, fd2;
// 	int pid;
// 	// ssize_t bytes_read;
// 	char *const ls_args[] = {"ls", "-l", "-a", NULL}; // Command and arguments for ls
// 	char *const env[] = {NULL};

// 	// char buffer[MAX_BUFFER_SIZE];

// 	// fd1 = open("test1", O_RDONLY);
// 	fd2 = open("test2", O_WRONLY | O_CREAT | O_TRUNC, 0666);

// 	pipe(pipefd);
// 	pid = fork();

// 	if (pid == 0)
// 	{    // child process
// 		close(pipefd[0]); // Close unused read end of the pipe

// 		// dup2(pipefd[1], STDOUT_FILENO);
// 		// while ((bytes_read = read(fd1, buffer, sizeof(buffer))) > 0)
// 		//     write(STDOUT_FILENO, buffer, bytes_read); // Write to the pipe
// 		execve("/bin/ls", ls_args, env);
// 		perror("execve");
// 		close(pipefd[1]);
// 		// close(fd1);
// 		return EXIT_SUCCESS; // Return success to indicate child completion
// 	}
// 	else
// 	{ // parent
// 		close(pipefd[1]);
// 		dup2(fd2, STDOUT_FILENO);
// 		wait(NULL);
// 	}

// 	close(pipefd[1]);
// 	close(pipefd[0]);
// 	// close(fd1);
// 	// close(fd2);

// 	return EXIT_SUCCESS;
// }