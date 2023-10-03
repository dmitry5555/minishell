/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:10:00 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/03 11:34:17 by dlariono         ###   ########.fr       */
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

	i = -1;
	subsplit = NULL;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, envlist);
		args[i] = expand_home(args[i], -1, envlist);
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