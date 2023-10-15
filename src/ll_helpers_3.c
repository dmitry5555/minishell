/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_helpers_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:16:48 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/15 18:21:34 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
