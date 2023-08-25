# include "minishell.h"

// if we have one++. -n flags we remove newline

void ft_echo(char **args)
{
	int i;
	int flag_n;

	flag_n = 0;

	i = 0; // where do we start??
	// printf("%d", nb_args(args)) for testing
	if (nb_args(args) > 1)
	{
		// remove all "-n" fro m the start and flag_n
 		while (args[i] && (ft_strcmp(args[i],"-n") == 0))
		{
			// printf("flag n \n");   for testing
			flag_n = 1;
			i++;
		}
		// continue with other args
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0])
				write(1, " ", 1);
			i++;
		}
	}
	if (!flag_n)
		write(1,"\n",1);
}

// int main(void)
// {
// 	char *args[] = { "-n", "-n", "world", NULL };
// 	ft_echo(args);
// }