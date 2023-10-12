/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:58:29 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/12 19:04:24 by dlariono         ###   ########.fr       */
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
			if (!check_exp_var(get_key_value_pair(cmd->cmd[i])[0])) // if varname is correct
			{
				// if we have "=" sign then the value is ""
				if (ft_strchr(cmd->cmd[i], '='))
				{
					printf("str is: %s \n", cmd->cmd[i]);
					printf("we hawe = \n");
					printf("value is: %s \n", get_key_value_pair(cmd->cmd[i])[1]);
					printf("size is: %lu \n", sizeof(get_key_value_pair(cmd->cmd[i])[1]));
					if ( ft_strcmp(get_key_value_pair(cmd->cmd[i])[1], "") )
						set_var(&env, get_key_value_pair(cmd->cmd[i])[0],
							get_key_value_pair(cmd->cmd[i])[1]);
					else
					{
						printf("set with empty string value: \n");
						set_var(&env, get_key_value_pair(cmd->cmd[i])[0], "");
					}
				}
				else
				{
					printf("set with NULL value: \n");
					set_var(&env, get_key_value_pair(cmd->cmd[i])[0], NULL);
				}
			}
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