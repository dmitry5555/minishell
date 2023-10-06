/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:10:00 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/06 20:50:53 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char **final_split(char **args, t_list *envlist)
{
	// expand_all(args, envlist);
	// args = ft_subsplit(args, "<|>", -1);
	// return (args);
	char	**subsplit;
	int		i;

	i = -1;
	subsplit = NULL;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, envlist);
		args[i] = expand_home(args[i], envlist);
		subsplit = ft_subsplit(args[i], "<|>");
		//ft_print_array(subsplit);
		ft_array_replace_in(&args, subsplit, i);
		i += ft_array_len(subsplit) - 1;
		ft_array_free(&subsplit);
	}
	return (args);
}
