/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_set_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:11:56 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/15 18:33:54 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_var(t_list **env, char *name, char *content)
{
	int		flag_upd;
	t_list	*curr;

	curr = NULL;
	flag_upd = 0;
	curr = (*env);
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			if (curr->content)
				free(curr->content);
			if (content)
				curr->content = ft_strdup(content);
			else
				curr->content = NULL;
			flag_upd = 1;
		}
		curr = curr->next;
	}
	if (!flag_upd)
		ft_add_new_node_end(env, name, content);
	return (0);
}

void	ft_free_node(t_list *node)
{
	if (node)
	{
		free(node->name);
		free(node->content);
		free(node);
	}
}

void	unset_var(t_list **env, char *name)
{
	t_list	*curr;
	t_list	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			ft_free_node(curr);
			if (prev)
				curr = prev->next;
			else
				curr = *env;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

// void	unset_var(t_list **env, char *name)
// {
// 	t_list	*curr;
// 	t_list	*prev;

// 	prev = NULL;
// 	curr = (*env);
// 	while (curr)
// 	{
// 		if (!ft_strcmp(curr->name, name))
// 		{
// 			if (prev)
// 			{
// 				prev->next = curr->next;
// 				free(curr->name);
// 				free(curr->content);
// 				free(curr);
// 				curr = prev->next;
// 			}
// 			else
// 			{
// 				*env = curr->next;
// 				free(curr->name);
// 				free(curr->content);
// 				free(curr);
// 				curr = *env;
// 			}
// 		}
// 		else
// 		{
// 			prev = curr;
// 			curr = curr->next;
// 		}
// 	}
// }
