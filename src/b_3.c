/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:58:29 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/12 17:59:13 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_cmd_node *cmd, t_list *env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	// ft_putstr_fd(cmd->cmd[0], 1);
	// ft_putstr_fd(cmd->cmd[1], 1);
	// ft_putstr_fd(cmd->cmd[2], 1);

	if (!cmd->cmd[1])
		ft_env_print(env, 1);
	else
	{
		while (cmd->cmd[++i])
		{
			if (!check_exp_var(get_key_value_pair(cmd->cmd[i])[0]))
				set_var(&env, get_key_value_pair(cmd->cmd[i])[0],
					get_key_value_pair(cmd->cmd[i])[1]);
			else if (!flag)
				flag = i;
		}
		if (flag)
		{
			ft_putstr_fd("export: not an identifier: ", 1);
			ft_putstr_fd(get_key_value_pair(cmd->cmd[flag])[0], 1);
			ft_putstr_fd("\n", 1);
		}
	}
	return (0);
}

// change shlvl on new minishell / exit
void	change_shlvl(t_list *env, int inc)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "SHLVL"))
			env->content = ft_itoa(ft_atoi(env->content) + inc);
		env = env->next;
	}
}

void	ft_unset(t_cmd_node *cmd, t_list *env)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		unset_var(&env, cmd->cmd[i]);
		i++;
	}
}