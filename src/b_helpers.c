/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:11:49 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/13 16:17:37 by dlariono         ###   ########.fr       */
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

void	ft_find_right_paths(t_cmdlist *cmd_list)
{
	t_cmdlist	*current;
	t_cmd_node	*node;
	int			flag;
	char		*cmd;

	current = cmd_list;
	while (current)
	{
		node = (t_cmd_node *)current->content;

		flag = 0;
		cmd = node->cmd[0];

		const char* arr[] =
		{
			"/usr/local/bin",
			"/usr/bin",
			"/bin",
			"/usr/sbin",
			"/sbin",
			"/usr/local/munki"
		};

		int total = sizeof(arr) / sizeof(arr[0]);

		while (total--)
		{
			char *tmp1 = ft_strjoin(arr[total], "/");
			char *tmp2 = ft_strjoin(tmp1, cmd);

			if (access(tmp2, X_OK) == 0)
			{
				// Free the old path string
				free(node->path);

				// Allocate memory for the new path and copy it
				node->path = strdup(tmp2);

				printf("⚪️ FT_FIND_RIGHT_PATH @ b_helpers.c\n");
				printf("Testing path - [%s]\n", tmp2);
				printf("Path [%s] is accessible. New path for this node is [%s]\n\n", arr[total], tmp2);
				flag = 1;
			}

			free(tmp1);
			free(tmp2);

			if (flag)
				break ;
		}
		current = current->next;
	}
}