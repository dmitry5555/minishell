/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:01:33 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/12 18:18:20 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_multiple(t_cmdlist *cmd_list, t_list *env, int *is_exit, int ncmds)
{
	while (cmd_list)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (!run_builtin(cmd_list, env, is_exit, ncmds))
			pre_run_single(cmd_list, env);
		cmd_list = cmd_list->next;
	}
	return (g_status);
}

void	exec_all(char *out, t_list *env)
{
	t_cmdlist	*cmd_list;
	char		**args;
	int			cmds_num;
	int			is_exit;

	cmd_list = NULL;
	if (out[0] != '\0')
		add_history(out);
	is_exit = 0;
	args = ft_split_cmds(out, " ");
	free(out);
	if (!args)
		ft_error(ERR_QUOTE, NULL, 1);
	if (args)
	{
		cmd_list = create_cmd_list(final_split(args, env), -1);
		if (!cmd_list)
			return ;
		ft_find_right_paths(cmd_list);
		cmds_num = ft_cmdlstsize(cmd_list);
		g_status = run_multiple(cmd_list, env, &is_exit, cmds_num);
		while (0 < cmds_num--)
		{
			waitpid(-1, &g_status, 0);
			//printf("gstatus = %d\n", g_status);
		}

		if (!is_exit && g_status == 13)
			g_status = 0;
		if (g_status > 255)
			g_status = g_status / 255;
		if (args && is_exit)
		{
			ft_cmdlstclear(&cmd_list, free_cmd_content);
			exit(g_status);
		}

		// end parse args
		// return (1);
	}
	ft_cmdlstclear(&cmd_list, free_cmd_content);
	//return (cmd_list);
}

int	main(int argc, char *argv[], char **env)
{
	t_list		*env_list;
	char		*out;

	g_status = 0;
	env_list = ft_env_parser(env);
	while (1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		out = readline("guest@minishell $ ");
		exec_all(out, env_list);
	}
	exit(g_status);
}