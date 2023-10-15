/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:58:29 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/15 18:44:18 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_cmd_node *cmd, t_list *env)
{
	int		i;
	char	**arr;

	i = 0;
	if (!cmd->cmd[1])
		ft_env_print(env, 1);
	else
	{
		while (cmd->cmd[++i])
		{
			arr = get_key_value_pair(cmd->cmd[i]);
			if (!check_exp_var(arr[0]))
			{
				if (ft_strchr(cmd->cmd[i], '='))
				{
					if (ft_strcmp(arr[1], ""))
						set_var(&env, arr[0], arr[1]);
					else
						set_var(&env, arr[0], "");
				}
				else
					set_var(&env, arr[0], NULL);
				ft_array_free(&arr);
			}
		}
	}
}

void	ft_unset(t_cmd_node *cmd, t_list **env)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		unset_var(env, &cmd->cmd[i][0]);
		i++;
	}
}

int	ft_env_print(t_list *env, int is_export)
{
	while (env)
	{
		if (is_export && env->name)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->name, 1);
			if (env->content)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(env->content, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		else if (env->content)
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->content, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	return (0);
}

int	check_exp_var(char *str)
{
	int	i;

	i = 0;
	if (('a' <= str[0] && str[0] <= 'z') || ('A' <= str[0] && str[0] <= 'Z'))
	{
		while (str[++i])
			if (!('a' <= str[i] && str[i] <= 'z')
				&& !('A' <= str[i] && str[i] <= 'Z')
				&& !('1' <= str[i] && str[i] <= '9'))
				return (1);
		return (0);
	}
	return (1);
}
