# include "minishell.h"

// print cmd list for testing
void	print_cmd_list(t_cmdlist *cmd_list)
{
	t_cmd_node *node;

	if (cmd_list != NULL)
		{
			while (cmd_list)
			{
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


void	exec_all(char *out, t_list *env)
{
	char **args;
	int		shlvl;
	t_cmdlist *cmd_list;
	t_cmd_node *node;

	cmd_list = NULL;
	if (!out)
	{
		printf("exit\n");
		return ;
	}
	if (out[0] != '\0')
		add_history(out);
	args = ft_split_cmds(out, " ");
	if (!args)
		ft_error(ERR_QUOTE, NULL, 2);
	if (args)
	{
		cmd_list = create_cmd_list(final_split(args, env), -1);
		print_cmd_list(cmd_list);
		ft_cmdlstclear(&cmd_list, free_cmd_content);
		// printf("AFTER FT_SPLIT_CMDS:\n");
		// ft_print_array(args);
	}
	free(out);
}


int	main(int argc, char *argv[], char **env)
{
	t_cmd_node	*node;
	t_cmdlist	*current;
	t_list		*env_list;

	char		*out;
	char		*shlvl;
	out = NULL;

	env_list = ft_env(env);

	while (argc && argv)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);

		out = readline("guest@minishell $ ");
		exec_all(out, env_list);

	}
}