/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:14:39 by justindaly        #+#    #+#             */
/*   Updated: 2023/10/09 18:59:09 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_node	*init_cmd_node(void)
{
	t_cmd_node	*node;

	node = malloc(sizeof(t_cmd_node));
	if (!node)
		return (NULL);
	node->cmd = NULL;
	node->path = NULL;
	node->in = STDIN_FILENO;
	node->out = STDOUT_FILENO;
	return (node);
}

int	ft_cmdlstsize(t_cmdlist *lst)
{
	int			i;
	t_cmdlist	*node;

	i = 0;
	node = lst;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

t_cmdlist	*ft_cmdlstnew(void *content)
{
	t_cmdlist	*list;

	list = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

void	ft_cmdlstadd_back(t_cmdlist **lst, t_cmdlist *newnode)
{
	t_cmdlist	*start;

	start = *lst;
	if (*lst)
	{
		while (start->next)
			start = start->next;
		start->next = newnode;
	}
	else
		*lst = newnode;
}

t_cmdlist	*ft_cmdlstlast(t_cmdlist *lst)
{
	t_cmdlist	*node;

	node = lst;
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}
