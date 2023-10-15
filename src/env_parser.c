/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:12:02 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/15 18:24:36 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// split single ENV string
char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*equal_sign_pos;

	equal_sign_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof(tmp) * (2 + 1));
	tmp[0] = ft_substr(arg, 0, equal_sign_pos - arg);
	tmp[1] = ft_substr(equal_sign_pos, 1, ft_strlen(arg));
	tmp[2] = NULL;
	return (tmp);
}

// env parser
t_list	*ft_env_parser(char **environ)
{
	t_list	*env;
	char	**env_lines;
	char	**temp;

	env = NULL;
	env_lines = environ;
	while (*env_lines)
	{
		temp = get_key_value_pair(*env_lines);
		if (!ft_strcmp(temp[0], "OLDPWD"))
			ft_add_new_node_end(&env, temp[0], NULL);
		else
			ft_add_new_node_end(&env, temp[0], temp[1]);
		ft_array_free(&temp);
		env_lines++;
	}
	return (env);
}
