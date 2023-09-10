/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:40:51 by jdaly             #+#    #+#             */
/*   Updated: 2023/09/10 22:52:40 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// void expand_vars(char *str, t_list *envlist)
// {
//     int	i = 0;
//     int j = 0;
//     char *bgn;
//     char *strcpy;
//     char *varname;
//     char *varvalue;

//     // printf("i = %d\n", i);


//     while (str[i]) //double
//     {
//         if (str[0] == 39)
// 			return ;

//         if (str[i] == '$' && str[i+1] != ' ' && str[i+1])
//         {
//             // str[i] = '#';
//             i++;
//             j = 0;
//             bgn = ft_substr(str, 0, i - 1);
//             printf("bgn = %s\n", bgn);
//             while(str[i] != '$' && str[i] != ' ' && str[i])
//             {
//                 j++;
//                 i++;
//             }
//         }
//         //save variable name
//         //join beginning of string and variable value and 
//         //printf("j is %d\n", j);
//         if (j > 0)
//         { 
//             ft_strlcpy(varname, &str[i - j], j + 1);
//             printf("varname = %s\n", varname);
//             varvalue = get_content_by_name(envlist, varname);
//             if (varvalue)
//                 strcpy = ft_strjoin(bgn, varvalue);
//             else
//                 strcpy = bgn;
//             printf("strcpy = %s\n", strcpy);
//             str = ft_strjoin(strcpy, &str[i + j]);
//             printf("str = %s\n", str);
//         }   
//         j = 0;
//         i++;
//     }
// }

void expand_vars(char *str, t_list *envlist)
{
    char *result = (char *)malloc(strlen(str) + 1); // Initialize an empty string
    ft_strlcpy(result, "", 1);

    int i = 0;

    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1])
        {
            i++;
            int j = 0;
            while (str[i] != ' ' && str[i])
            {
                j++;
                i++;
            }

            if (j > 0)
            {
                char *varname = (char *)malloc(j + 1); // Allocate memory for variable name
                strncpy(varname, &str[i - j], j);
                varname[j] = '\0';

                char *varvalue = get_content_by_name(envlist, varname);
                free(varname);

                if (varvalue)
                    strcat(result, varvalue);
                    // No variable found, skip the $variable (including '$')
            }
        }
        else
        {
            // Copy characters other than '$' and spaces to the result
            char temp[2] = {str[i], '\0'};
            ft_strlcat(result, temp, ft_strlen(result) + ft_strlen(temp));
            i++;
        }
    }

    // Update the original string
    ft_strlcpy(str, result, ft_strlen(str) + ft_strlen(result));
    free(result);
}

// int main(void)
// {
//     char *str = ft_strdup("hello $novar your home directory is: $HOME");
//     t_list *envlist = ft_env();

//     expand_vars(str, envlist);
//     printf("str = %s\n", str);

//     // Don't forget to free memory allocated for str and envlist when done.
//     free(str);
//     //ft_lstclear(envlist, &del);
//     return 0;
// }

// int main(void)
// {

//     char    *str = "hello $VARIABLE end of the string";
//     t_list  *envlist = ft_env();
//     // char    *str = "$var1 string";
//     // char    *str = "$var1 string";

//     expand_vars(str, envlist);
// }