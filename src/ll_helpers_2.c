/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_helpers_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:16:17 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/15 18:21:39 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  Deletes and frees the given node and every
//  successor of that node, using the function ’del’
//  and free(3).
//  Finally, the pointer to the list must be set to
//  NULL.

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*node;

	if (lst == 0 || del == 0)
		return ;
	temp = *lst;
	while (temp)
	{
		node = temp->next;
		del(temp->content);
		free(temp);
		temp = node;
	}
	*lst = 0;
}
// Takes as a parameter a node and frees the memory of
// the node’s content using the function ’del’ given
// as a parameter and free the node.  The memory of
// ’next’ must not be freed.

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == 0 || del == 0)
		return ;
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}
// Iterates the list ’lst’ and applies the function
// ’f’ on the content of each node.

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*node;
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		node = temp->next;
		f(temp->content);
		temp = node;
	}
}
// Returns the last node of the list.

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*node;

	node = lst;
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

char	*env_cont(t_list *head, const char *name)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		if (!ft_strcmp(current->name, name))
			return (current->content);
		current = current->next;
	}
	return (NULL);
}
