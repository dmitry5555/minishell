/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_part_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:19:28 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/15 18:19:42 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_shlvl(t_list *env)
{
	int		lvl;
	char	*str;

	while (env)
	{
		if (!ft_strcmp(env->name, "SHLVL"))
		{
			str = env->content;
			lvl = ft_atoi(str) + 1;
			free(env->content);
			env->content = ft_itoa(lvl);
		}
		env = env->next;
	}
}

int	ft_is_dir(char *cmd)
{
	int	i;
	int	dot;
	int	slash;

	i = 0;
	dot = 0;
	slash = 0;
	while (cmd[i])
	{
		if (cmd[i] == 46)
			dot++;
		if (cmd[i] == 47)
		{
			slash++;
			if (dot < 3)
				dot = 0;
		}
		if (cmd[i] != 47 && cmd[i] != 46)
			return (0);
		i++;
	}
	if (dot < 3 && 0 < slash)
		return (1);
	return (0);
}
