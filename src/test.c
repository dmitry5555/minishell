# include "minishell.h"

// int main()
// {

// 	char *arr1[] = {"ls", "ls", "-1"};
// 	char *arr2[] = {"wc", "wc", "-l"};
// 	char *arr3[] = {"grep", "grep", "5"};
// 	int fd[2];
// 	pid_t pid;

// 	pipe(fd);
// 	pid = fork();

// 	if (pid != 0)
// 	{
// 		dup2(fd[1],1);
// 		close(fd[0]);
// 		execlp("ls", "ls", "-1", NULL);
// 		perror("execlp");
// 	}
// 	else
// 	{
// 		dup2(fd[0], 0);
// 		close(fd[1]);
// 		execlp("wc", "wc", "-l", NULL);
// 		perror("execlp");
// 	}

// }