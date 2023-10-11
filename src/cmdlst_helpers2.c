/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 00:23:42 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/12 00:38:18 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd_content(void *content)
{
	t_cmd_node	*node;

	node = content;
	ft_array_free(&node->cmd);
	free(node->path);
	if (node->in != STDIN_FILENO)
		close(node->in);
	if (node->out != STDOUT_FILENO)
		close(node->out);
	free(node);
}

void	ft_cmdlstclear(t_cmdlist **lst, void (*del)(void*))
{
	t_cmdlist	*start;
	t_cmdlist	*temp;

	if (!lst)
		return ;
	start = *lst;
	temp = NULL;
	while (start)
	{
		temp = start;
		start = start->next;
		del(temp->content);
		free(temp);
	}
	*lst = NULL;
}

t_cmdlist	*fill_cmdlst_error(t_cmdlist *cmds, char **args, char **tmp)
{
	ft_cmdlstclear(&cmds, free_cmd_content);
	ft_array_free(&tmp);
	ft_array_free(&args);
	return (NULL);
}
