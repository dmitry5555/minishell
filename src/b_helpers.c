/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:11:49 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/14 15:01:38 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *str)
{
	int	size;

	const char* b_in[] =
	{
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
	};
	size = sizeof(b_in) / sizeof(b_in[0]);
	while (size--)
	{
		if (!ft_strcmp(b_in[size], str))
			return (1);
	}
	return (0);
}

// void ft_find_right_path(t_list **t_cmd_node)

// loop throuh working paths ftom ENV and test if cmd can run
// if ok writes new path to node->path
int	ft_find_right_2(char **arr, t_cmdlist *cmd_list)
{
	int			i;
	int			flag;
	char		*tmp2;
	char		*tmp3;

	i = 0;
	flag = 0;
	while (arr[++i])
	{
		if (ft_strcmp(arr[i], ":"))
		{
			tmp2 = ft_strjoin(arr[i],"/");
			tmp3 = ft_strjoin(tmp2, ((t_cmd_node *)cmd_list->content)->cmd[0]);
			if (access(tmp3, X_OK) == 0)
			{
				((t_cmd_node *)cmd_list->content)->path = ft_strdup(tmp3);
				flag = 1;
			}
			free(tmp2);
			free(tmp3);
			if (flag)
				break ;
		}
	}
	return (flag);
}

void	ft_find_right_paths(t_cmdlist *cmd_list, t_list *env)
{
	int		flag;
	char	*cmd;
	char	*tmp;
	char	**arr;

	while (cmd_list)
	{
		cmd = ((t_cmd_node *)cmd_list->content)->cmd[0];
		tmp = env_cont(env, "PATH");
		arr = ft_subsplit(tmp, ":");
		printf("testing  🟠 : [%s]  \n", tmp);
		flag = ft_find_right_2(arr, cmd_list);
		if (!flag)
			((t_cmd_node *)cmd_list->content)->path = ft_strdup(cmd);
		ft_array_free(&arr);
		cmd_list = cmd_list->next;
	}
}
