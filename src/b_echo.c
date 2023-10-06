# include "minishell.h"

// if we have one++. -n flags we remove newline

void ft_echo(char **args)
{
	int i;
	int flag_n;

	flag_n = 0;

	i = 0;
	if (nb_args(args) > 1)
	{
		// remove all "-n" fro m the start and flag_n
		while(args[i++] && args[i][0] == '-')
		{
			// if (args[i][0] == '-')
			// {
				int j = 1;
				while (args[i][j] == 'n') //&& ((args[i][j + 1]) == ' ' || args[i][j + 1] == 'n'))
					j++;
				if (args[i][j] == '\0')
				{
					flag_n = 1;
				}
				// else
				// 	i--;
				// while(args[i] != ' ')
			// }
			// i += j;
		}
		if (!flag_n)
			i--;
		// continue with other args
		// i = 0;
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