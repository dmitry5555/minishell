/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:10:00 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/02 16:58:25 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **final_split(char **args, t_list *envlist)
{
	// expand_all(args, envlist);
	// args = ft_subsplit(args, "<|>", -1);
	// return (args);
	char	**subsplit;
	int		i;
	int		in_sq;
	int		in_dq;

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, in_sq, in_dq, envlist);
		//args[i] = expand_path();
		subsplit = ft_subsplit(args[i], "<|>");
		//ft_print_array(subsplit);
		ft_array_replace_in(&args, subsplit, i);
		i += ft_array_len(subsplit) - 1;
		ft_array_free(&subsplit);
	}
	return (args);
}

// change shlvl on new minishell / exit
void change_shlvl(t_list *env, int inc)
{
	char *shlvl;

	while(env)
	{
		if (!ft_strcmp(env->name, "SHLVL"))
		{
			env->content = ft_itoa(ft_atoi(env->content) + 1);
			// set_var(&env, "SHLVL", "2");
		}
		env = env->next;
	}
}

void	check_args(char *out, t_list *env)
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
		// printf("AFTER FT_SPLIT_CMDS:\n");
		// ft_print_array(args);
	}
	free(out);

	cmd_list = create_cmd_list(final_split(args, env), -1);
	// ft_find_right_paths(cmd_list);
	// while (cmd_list)
	// {
	// 	node = cmd_list->content;
	// 	// if (!ft_strcmp(node->cmd[0], "./minishell"))
	// 	// 	change_shlvl(env, 1);
	// 	// exec_cmd(cmd_list, env);
	// 	cmd_list = cmd_list->next;
	// }
	print_cmd_list(cmd_list);

	// return (cmd_list);
	// ft_cmdlstclear(&cmd_list, free_cmd_content);

}

int	main(int argc, char *argv[], char **env)
{
	t_cmd_node	*node;
	t_cmdlist	*current;
	t_cmdlist	*cmd_list;
	t_list		*env_list;
	char		*str;
	char		*out;
	char		*shlvl;
	cmd_list = NULL;
	out = NULL;

	env_list = ft_env(env);

	while (argc && argv)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);

		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell $ ");
		free(str);
		check_args(out, env_list);
	}
	ft_cmdlstclear(&cmd_list, free_cmd_content);
}