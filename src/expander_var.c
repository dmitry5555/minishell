/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:40:51 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/12 15:42:26 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;
/* cases to handle
    1. $VARIABLE
    2. $VARIABLE_$VARIABLE --> jdaly
    3. $? --> expand to exit status

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

char	*get_value(char *varname, t_list *envlist)
{
	char	*varvalue;

	if (ft_strcmp("?", varname) == 0)
		varvalue = ft_itoa(g_status);
	else
		varvalue = env_cont(envlist, varname);
	free(varname);
	if (!varvalue)
		return (NULL);
	return (ft_strdup(varvalue));
}

static char	*get_substr_var(char *str, int i, t_list *envlist)
{
	char	*aux;
	int		pos;
	char	*path;
	char	*val;
	char	*varname;

	pos = ft_strchars_i(&str[i], "|\"\'$?>< .")
		+ (ft_strchr("$?", str[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(str) - 1;
	aux = ft_substr(str, 0, i - 1);
	varname = ft_strndup(&str[i], pos);
	val = get_value(varname, envlist);
	path = ft_strjoin(aux, val);
	free(val);
	free(aux);
	aux = ft_strjoin(path, &str[i + pos]);
	free(path);
	free(str);
	return (aux);
}

char	*expand_vars(char *str, int i, t_list *envlist)
{
	int	in_sq;
	int	in_dq;

	in_sq = 0;
	in_dq = 0;
	while (str && str[++i])
	{
		in_sq = (in_sq + (!in_dq && str[i] == '\'')) % 2;
		in_dq = (in_dq + (!in_sq && str[i] == '\"')) % 2;
		if (!in_sq && str[i] == '$' && str[i + 1] && \
			((ft_strchars_i(&str[i + 1], "/~%^{}:; ") && !in_dq) || \
			(ft_strchars_i(&str[i + 1], "/~%^{}:;\"") && in_dq)))
			return (expand_vars(get_substr_var(str, ++i, envlist),
					-1, envlist));
	}
	return (str);
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