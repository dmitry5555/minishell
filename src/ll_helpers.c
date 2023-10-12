/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:12:19 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/12 17:31:40 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_new_node_end(t_list **env, const char *str1, const char *str2)
{
	t_list	*new;
	t_list	*temp;

	new = malloc(sizeof(t_list));
	new->name = NULL;
	new->content = NULL;
	if (str1)
		new->name = ft_strndup(str1, ft_strlen(str1) + 1);
	if (str2)
		new->content = ft_strndup(str2, ft_strlen(str2) + 1);
	new->next = NULL;
	if (*env == NULL)
	{
		*env = new;
	}
	else
	{
		temp = *env;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_add_new_node_start(t_list **env, const char *str1, const char *str2)
{
	t_list	*new;
	t_list	*current;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->name = ft_strndup(str1, ft_strlen(str1) + 1);
	new->content = ft_strndup(str2, ft_strlen(str2) + 1);
	new->next = NULL;
	if (*env == NULL)
		*env = new;
	else
	{
		current = *env;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void	ft_cleanup(t_list **env)
{
	ft_free_list(*env);
	*env = NULL;
}

void	ft_free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->name);
		free(temp->content);
		free(temp);
	}
}

// Counts the number of nodes in a list.

int ft_lstsize(t_list *lst)
{
	int 	i;
	t_list	*node;

	i = 0;
	node = lst;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

// Adds the node ’new’ at the end of the list.

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
}

// Adds the node ’new’ at the beginning of the list.

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
}
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