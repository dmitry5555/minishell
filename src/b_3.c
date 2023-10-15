/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:58:29 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/13 16:25:31 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_cmd_node *cmd, t_list *env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	char **arr;

	if (!cmd->cmd[1])
		ft_env_print(env, 1);
	else
	{
		while (cmd->cmd[++i])
		{
			arr = get_key_value_pair(cmd->cmd[i]);
			if (!check_exp_var(arr[0])) // if varname is correct
			{
				// if we have "=" sign then the value is ""
				if (ft_strchr(cmd->cmd[i], '='))
				{
					printf("str is: %s \n", cmd->cmd[i]);
					printf("name is:  %s \n", arr[0]);
					printf("value is: %s \n", arr[1]);
					printf("size is: %lu \n", sizeof(arr[1]));
					if ( ft_strcmp(arr[1], "") )
						set_var(&env, arr[0],
							arr[1]);
					else
					{
						printf("set with empty string value: \n");
						set_var(&env, arr[0], "");
					}
				}
				else
				{
					printf("set with NULL value: \n");
					set_var(&env, arr[0], NULL);
				}
				ft_array_free(&arr);
			}
			else if (!flag)
				flag = i;
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
