/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_home.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:24:34 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/02 18:38:03 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  5. ~ --> /Users/jdaly
    //////6. ~jdaly --> /Users/jdaly
*/

int is_user_home(char *str, t_list *envlist)
{
	char	*user_id;

	user_id = get_content_by_name(envlist, "USER");
	if ((strncmp(str, "~", 1) == 0) && strncmp(&str[1], user_id, (size_t)ft_strlen(user_id)) == 0)
		return (1);
	else
		return (0);
}

char    *expand_home(char *str, int i, t_list *envlist)
{
    char    *result;
    char    *home;
    char    *before;
    int     in_sq;
    int     in_dq;

    in_sq = 0;
    in_dq = 0;
    home = get_content_by_name(envlist, "HOME");
    while (str && str[++i])
    {
        in_sq = (in_sq + (!in_dq && str[i] == '\'')) % 2;
		in_dq = (in_dq + (!in_sq && str[i] == '\"')) % 2;
		if (!in_sq && !in_dq && str[i] == '~' && (i == 0 || \
			str[i - 1] != '$'))
		{
            // if (is_user_home(&str[i], envlist))
            //     home = 
			before = ft_substr(str, 0, i);
			result = ft_strjoin(before, home);
			free(before);
			before = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(result, before);
			free(before);
			free(result);
			return (expand_home(str, i + ft_strlen(home) - 1, envlist));
		}
	}
	return (str);
}

// int main(void)
// {

//     char    *str = "this is a string ~ jdaly~";
//     t_list  *envlist = ft_env();
//     // char    *str = "$var1 string";
//     // char    *str = "$var1 string";

//     printf("str = [%s]\n", str);
// 	str = expand_home(str, envlist);
// 	printf("str = [%s]\n", str);
//     free(str);
//     ft_cleanup(&envlist);
// }