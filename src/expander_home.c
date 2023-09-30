/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_home.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:24:34 by jdaly             #+#    #+#             */
/*   Updated: 2023/09/30 18:22:20 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  5. ~ --> /Users/jdaly
    6. ~jdaly --> /Users/jdaly
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

char    *expand_home(char *str, t_list *envlist)
{
    int     i;
    char    *varvalue;
    char    *tmp_result;
    char    *tmp_char;
    char    *result;

    result = ft_strdup("");
    i = -1;
    while (str[++i])
    {
        //printf("str[i] = %c\n", str[i]);
        if (i == 0 && (str[i] == '~' || (is_user_home(&str[i], envlist))))
        {
            varvalue = get_content_by_name(envlist, "HOME");
            printf("varvalue = [%s]\n", varvalue);
            tmp_result = ft_strjoin(result, varvalue);
            if (tmp_result)
            {
                free(result);
                result = tmp_result;
            }
            if (is_user_home(&str[i], envlist))
                i += ft_strlen(get_content_by_name(envlist, "USER"));
        }
        else
        {
            tmp_char = strndup(&str[i], 1);
            //printf("tmp_char = %s\n", tmp_char);
            tmp_result = ft_strjoin(result, tmp_char);
            free(result);
            result = tmp_result;
            free(tmp_char);
            //free(tmp_result);
        }
		//printf("result = %s\n\n", result);
    }
	printf("result = %s\n\n", result);
    return (result);
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