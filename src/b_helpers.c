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

void	ft_find_right_paths(t_cmdlist *cmd_list, t_list *env)
{
	t_cmdlist	*current;
	t_cmd_node	*node;
	int			flag;
	char		*cmd;
	int			i;
	char		*tmp;
	char		*tmp2;
	char		*tmp3;
	char		**arr;

	current = cmd_list;
	while (current)
	{
		node = (t_cmd_node *)current->content;
		flag = 0;
		cmd = node->cmd[0];

		// int total = sizeof(arr) / sizeof(arr[0]);
		tmp = env_cont(env, "PATH");
		arr = ft_subsplit(tmp, ":");
		// free (tmp);
		i = 0;
		printf("testing  🟠 : [%s]  \n", tmp);

		while (arr[i]) // each PATH
		{
			if (ft_strcmp(arr[i], ":"))
			{
				tmp2 = ft_strjoin(arr[i],"/");
				tmp3 = ft_strjoin(tmp2, cmd);
				printf("testing 🟡 PATH : [%s]   CMD : [%s]  \n", arr[i], cmd);
				if (access(tmp3, X_OK) == 0)
				{
					free(node->path);
					node->path = ft_strdup(tmp3);
					printf("🟢 Path [%s] is accessible. New path for this node is [%s]\n\n", arr[i], tmp3);
					flag = 1;
				}
				free(tmp2);
				free(tmp3);
				if (flag)
					break ;
			}
			i++;
		}

		// free(tmp2);
		ft_array_free(&arr);
		current = current->next;
	}
}