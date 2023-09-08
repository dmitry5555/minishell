# include "minishell.h"

void	ft_cd(t_list **env, char *name, char *content, int is_env)
{
	char *input;

	// change current path in ENV
	set_var(env, name, content, 1);
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