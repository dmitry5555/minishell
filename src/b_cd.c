# include "minishell.h"

void	ft_cd(t_cmd_node *node, t_list *env)
{
	char *new_path;
	// char *input;
	// if args == 1  path  = home

	// if args > 1
	printf("💽\n");
	if (!node->cmd[1])
		new_path = get_content_by_name(env, "HOME");
	else if (node->cmd[1])
		new_path = ft_strdup(node->cmd[1]);
	printf("newpath is: [%s] \n", new_path);
	chdir(new_path);

			// if  arg[1][0] == '~'
			// 	new = ar gs[1]
			// 	path = join( home + args1)  // concat portion of argument with home

			// else if 	strcmp(args1 , "-")
			// 	path = oldpwd
			// else
			// 	path = args[1]
}

// int	main()
// {
// 	char *input;
// 	while ((input = readline("Enter something: ")) != NULL)
// 	{
// 		// modify_and_redisplay(input);
// 		if (input)
// 		{
// 			// rl_on_new_line();
// 			// rl_replace_line("111", "123");
// 			// add_history("132");
// 			// rl_replace_line("123");
// 			// clear_history();
// 		}
// 		free(input);
// 	}
// 	return (0);
// }