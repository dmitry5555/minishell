/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:40:51 by jdaly             #+#    #+#             */
/*   Updated: 2023/09/13 21:49:02 by jdaly            ###   ########.fr       */
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

char    *get_varname(char *str, int bgn, int *end)
{
    int tmp_end;
    
    tmp_end = bgn;
	if ((str[tmp_end] == '$' && !str[tmp_end + 1]) || str[tmp_end + 1] == ' ' || str[tmp_end + 1] == '$')
    {
        *end = tmp_end + 1;
		return (ft_strdup("$$"));
    }
    else if ((str[tmp_end] == '?' && !str[tmp_end + 1]) || str[tmp_end + 1] == ' ' || str[tmp_end + 1] == '$')
    {
        *end = tmp_end + 1;
        return (ft_strdup("$?"));
    }
    else 
    {
        while (str[tmp_end] && str[tmp_end] != ' ' && (ft_isalnum(str[tmp_end]) || str[tmp_end] == '_'))
            tmp_end++;
        *end = tmp_end;
    }
    return (ft_strndup(&str[bgn], tmp_end - bgn));
}

char    *get_value(char *varname, t_list *envlist)
{
    char *varvalue;

    if (ft_strcmp("$$", varname) == 0)
        varvalue = "PID"; //replace with PID;
    else if (ft_strcmp("$?", varname) == 0)
        varvalue = "GLOBAL_VAR"; //replace with global variable
    else
        varvalue = get_content_by_name(envlist, varname);
    if (!varvalue)
        varvalue = "";
    free(varname);
    return (varvalue);
}

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
        //printf("str[i] = %c\n", str[i]);
        if (str[i] == '$' && str[i + 1])
        {
            i++;
            varname = get_varname(str, i, &var_end);
            //printf("varname = [%s]\n", varname);
			if (strcmp(varname, "$") == 0)
				varvalue = "$";
            else
                varvalue = get_value(varname, envlist);
            //printf("varvalue = [%s]\n", varvalue);
            if (varvalue != NULL)
            {
                tmp_result = ft_strjoin(result, varvalue);
                if (tmp_result)
                {
                    free(result);
                    result = tmp_result;
                    //free(tmp_result);
                }
            }
            i = var_end - 1;
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
    return (result);
}

void    expand_all(char **args, t_list *envlist)
{
    char    *temp;
    char    *temp2;
    int     i;

    i = -1;
    while (args && args[++i])
    {
        if (args[i][0] != '\'' && args[i][ft_strlen(args[i]) - 1] != '\'')
        {
            temp = expand_vars(args[i], envlist);
            if (temp)
            {
                free(args[i]);
                args[i] = temp;
            }

        }
        if ((args[i][0] != '\'' && args[i][ft_strlen(args[i]) - 1] != '\'')
            || (args[i][0] != '"' && args[i][ft_strlen(args[i]) - 1] != '"'))
        {
            temp2 = expand_home(args[i], envlist);
            free(args[i]);
            args[i] = temp2;
        }
    }
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

//     char    *str = "this is a string $USER $USER $$$$";
//     t_list  *envlist = ft_env();
//     // char    *str = "$var1 string";
//     // char    *str = "$var1 string";

//     printf("str = [%s]\n", str);
// 	str = expand_vars(str, envlist);
// 	printf("str = [%s]\n", str);
//     free(str);
//     ft_cleanup(&envlist);
// }

// int main(void)
// {
//     char **array = malloc(sizeof(char *) * 6);
//     array[0] = ft_strdup("~");
//     array[1] = ft_strdup("\"hello $USER\"");
//     array[2] = ft_strdup("\'hello $USER\'");
//     array[3] = ft_strdup("$PATH");
//     array[4] = ft_strdup("\"this is a long string with quotes.\"");
//     array[5] = NULL;

//     t_list *envlist = ft_env();

//     ft_print_array(array);
//     expand_all(array, envlist);
//     ft_print_array(array);

//     ft_array_free(&array);
//     ft_cleanup(&envlist);
// }