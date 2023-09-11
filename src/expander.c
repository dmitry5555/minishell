/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:40:51 by jdaly             #+#    #+#             */
/*   Updated: 2023/09/11 22:18:35 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/* cases to handle
    1. $VARIABLE
    2. $VARIABLE_$VARIABLE --> jdaly
    3. $? --> expand to exit status
    4. $$ --> expand to pid

    5. ~ --> /Users/jdaly
    6. ~jdaly --> /Users/jdaly
    
*/

int	ft_isalnum(int c)
{
	if (!(((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
			|| (c >= '0' && c <= '9')))
		return (0);
	else
		return (1);
}

int	ft_isequalstrn(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (s1 == s2)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (!(s1[i] == '\0' && s2[i] == '\0'))
	{
		if (n > 0 && i >= n)
			break ;
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

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

// char    *get_varname(char *str)
// {
//     char *varname;
//     int i = -1;

//     varname = NULL;
//     while (str[++i])
//     {
//         if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1])
//         {
//             i++;
//             int j = 0;
//             if (str[i] == '$')
//             {
//                 varname = strdup("$$");
//                 break ;
//             }
//             while (str[i] != ' ' && str[i] && ft_isalnum(str[i]) || str[i] == '_')
//             {
//                 j++;
//                 i++;
//             }

//             if (j > 0)
//             {
//                 varname = strndup(&str[i - j], j);
//                 varname[j] = '\0';
//                 break ;
//             }
//         }
//     }
//     return (varname);
// }

// void expand_vars_recursive(char *str, t_list *envlist)
// {
//     char    *result;
//     char    *varname;
//     char    *varvalue;
//     int     varfound;
    
//     result = (char *)malloc(strlen(str) + 1); // Initialize an empty string
//     strcpy(result, ""); // Use strcpy for the initial empty string
//     int i = 0;
//     varfound = 0;
//     while (str[i])
//     {
//         varfound = 1;
//         if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1])
//         {
//             i++;
//             int j = 0;
//             while (str[i] != ' ' && str[i])
//             {
//                 j++;
//                 i++;
//             }
//             if (j > 0) 
//             {
//                 varname = (char *)malloc(j + 1); // Allocate memory for variable name
//                 strncpy(varname, &str[i - j], j);
//                 varname[j] = '\0';

//                 varvalue = get_content_by_name(envlist, varname);
//                 free(varname);

//                 if (varvalue) {
//                     strcat(result, varvalue);
//                 }
//                 // No variable found, skip the $variable (including '$')
//             }
//         }
//         else {
//             // Copy characters other than '$' and spaces to the result
//             char temp[2] = {str[i], '\0'};
//             strcat(result, temp);
//             i++;
//         }
//     }

//     // Update the original string
//     if (varfound)
//         strcpy(str, result);
//     free(result);

//     // Check if there are more variables to expand recursively
//     if (varfound && strstr(str, "$"))
//         expand_vars_recursive(str, envlist);
// }

char    *get_varname(char *str, int bgn, int *end)
{
    int tmp_end;
    
    tmp_end = bgn;
    while (str[tmp_end] && str[tmp_end] != ' ' && str[bgn] && ft_isalnum(str[bgn]) || str[bgn] == '_')
        tmp_end++;
    *end = tmp_end;
    return (ft_strndup(&str[bgn], tmp_end - bgn));
}

// void    expand_all(char **args, t_list envlist)
// {
//     while (args)
//     {
//         if (args[i][0] != '\'' && args[i][ft_strlen(args[i] - 1) != '\''])
//             expand_vars(args[i]);
        
//     }
// }

char    *expand_vars(char *str, t_list *envlist)
{
    int     i;
    char    *varname;
    char    *varvalue;
    char    *tmp_result;
    char    *tmp_char;
    char    *result;
    int     var_end;

    result = ft_strdup("");
    i = -1;
    var_end = 0;
    while (str[++i])
    {
        if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
        {
            i++;
            varname = get_varname(str, i, &var_end);
            printf("varname = %s\n", varname);
            varvalue = get_content_by_name(envlist, varname);
            printf("varvalue = %s\n", varvalue);
            free(varname);
            if (varvalue)
            {
                tmp_result = ft_strjoin(result, varvalue);
                if (tmp_result)
                {
                    free(result);
                    result = tmp_result;
                    printf("tmp result: %s\n", tmp_result);
                }
                i = var_end;
            }
            else
                i++;
        }
        else
        {
            tmp_char = strndup(&str[i], 1);
            //printf("tmp_char = %s\n", tmp_char);
            result = ft_strjoin(result, tmp_char);
            free(tmp_char);
        }
    }
    return (result);
}

// int main(void)
// {
//     char *str = ft_strdup("hello $USER");
//     t_list *envlist = ft_env();
//     char *varname;

//     // varname = get_varname(str);
//     // printf("varname = %s\n", varname);
//     expand_vars(str, envlist);
//     printf("str = %s\n", str);

//     // Don't forget to free memory allocated for str and envlist when done.
//     free(str);
//     //free(varname);
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