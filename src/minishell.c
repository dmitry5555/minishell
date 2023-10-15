/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:01:33 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/13 19:02:42 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_multiple(t_cmdlist *cmd_list, t_list *env, int *is_exit, int ncmds, char **env_arr)
{
	while (cmd_list)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (!run_builtin(cmd_list, env, is_exit, ncmds))
			pre_run_single(cmd_list, env, env_arr);
		cmd_list = cmd_list->next;
	}
	return (g_status);
}

void exec_all_part2(t_list *env, int is_exit, char **args, char **env_arr)
{
	t_cmdlist	*cmd_list;
	int			cmds_num;

	cmd_list = NULL;
	cmd_list = create_cmd_list(final_split(args, env), -1);
	if (!cmd_list)
		return ;
	ft_find_right_paths(cmd_list, env);
	cmds_num = ft_cmdlstsize(cmd_list);
	g_status = run_multiple(cmd_list, env, &is_exit, cmds_num, env_arr);
	while (0 < cmds_num--)
		waitpid(-1, &g_status, 0);
	if (g_status > 255)
		g_status = g_status / 255;
	if (args && is_exit)
	{
		ft_cmdlstclear(&cmd_list, free_cmd_content);
		exit(g_status);
	}
	ft_cmdlstclear(&cmd_list, free_cmd_content);
}

void	exec_all(char *out, t_list *env, char **env_arr)
{
	t_cmdlist	*cmd_list;
	char		**args;
	int			is_exit;

	cmd_list = NULL;
	if (!out) // for ctrl+d
	{
		printf("exit\n");
		exit(g_status);
	}
	if (out[0] != '\0')
		add_history(out);
	is_exit = 0;
	args = ft_split_cmds(out, " ");
	free(out);
	if (!args)
		ft_error(ERR_QUOTE, NULL, 1);
	if (!args)
		return ;
	if (args)
		exec_all_part2(env, is_exit, args, env_arr);
}

int	main(int argc, char *argv[], char **env)
{
	t_list		*env_list;
	char		*out;
	char		**env_arr;

	env_arr = env;
	g_status = 0;
	env_list = ft_env_parser(env);
	while (argc && argv)
	{
		signal(SIGINT, sig_hand); // ctrl-x = our handler
		signal(SIGQUIT, SIG_IGN); // ctrl-\ = ignore
		out = readline("guest@minishell $ ");
		exec_all(out, env_list, env_arr);
	}
}