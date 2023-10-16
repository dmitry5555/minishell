/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:01:33 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/16 13:31:03 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_to_arr(t_list *env)
{
	int		len;
	int		i;
	char	**env_arr;

	i = 0;
	env_arr = malloc((ft_lstsize(env) + 1) * sizeof(char *));
	while (env)
	{
		len = ft_strlen(env->name) + 1 + ft_strlen(env->content);
		env_arr[i] = malloc(len + 1);
		env_arr[i] = ft_strjoin(env->name, "=");
		env_arr[i] = ft_strjoin(env_arr[i], env->content);
		i++;
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

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

void	exec_all_part2(t_list *env, int is_exit, char **args)
{
	t_cmdlist	*cmd_list;
	int			cmds_num;

	cmd_list = NULL;
	cmd_list = create_cmd_list(final_split(args, env), -1);
	if (!cmd_list)
		return ;
	ft_find_right_paths(cmd_list, env);
	cmds_num = ft_cmdlstsize(cmd_list);
	g_status = run_multiple(cmd_list, env, &is_exit, cmds_num);
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

void	exec_all(char *out, t_list *env)
{
	t_cmdlist	*cmd_list;
	char		**args;
	int			is_exit;

	cmd_list = NULL;
	if (!out)
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
		exec_all_part2(env, is_exit, args);
}

int	main(int argc, char *argv[], char **env)
{
	t_list		*env_list;
	char		*out;

	g_status = 0;
	env_list = ft_env_parser(env);
	change_shlvl(env_list);
	while (argc && argv)
	{
		signal(SIGINT, sig_hand);
		signal(SIGQUIT, SIG_IGN);
		out = readline("guest@minishell $ ");
		exec_all(out, env_list);
	}
}
