/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:12:19 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/15 18:16:38 by dlariono         ###   ########.fr       */
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

int	ft_lstsize(t_list *lst)
{
	int		i;
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
