/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:40:51 by jdaly             #+#    #+#             */
/*   Updated: 2023/08/24 18:41:01 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void expand_vars(char *str)
{
    int	i = 0;
    int j = 0;
    char *bgn;
    char *strcpy;
    char *varname;

    // printf("i = %d\n", i);


    while (str[i]) //double
    {
        if (str[0] == 39)
			return ;

        if (str[i] == '$' && str[i+1] != ' ' && str[i+1])
        {
            // str[i] = '#';
            i++;
            j = 0;
            bgn = ft_substr(str, 0, i - 1);
            printf("bgn = %s\n", bgn);
            while(str[i] != '$' && str[i] != ' ' && str[i])
            {
                j++;
                i++;
            }
        }
        //save variable name
        //join beginning of string and variable value and 
        //printf("j is %d\n", j);
        if (j > 0)
        { 
            ft_strlcpy(varname, &str[i - j], j + 1);
            printf("varname = %s\n", varname);
            strcpy = ft_strjoin(bgn, "variablevalue");
            printf("strcpy = %s\n", strcpy);
            str = ft_strjoin(strcpy, &str[i + j]);
            printf("str = %s\n", str);
        }   
        j = 0;
        i++;
    }
}

// int main(void)
// {

//     char    *str = "hello $var1 the $end";
//     // char    *str = "$var1 string";
//     // char    *str = "$var1 string";

//     expand_vars(str);
// }