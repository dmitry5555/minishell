# include "minishell.h"

// parse key value

char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*equal_sign_pos;

	// equal_sign_pos =
	equal_sign_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof(tmp)*(2+1));
	tmp[0] = ft_substr(arg, 0, equal_sign_pos - arg);
	tmp[1] = ft_substr(equal_sign_pos, 1, ft_strlen(arg));
	tmp[2] = NULL;
	return(tmp);
}

//for testing, didnt test for leaks, need to free in main
// int main()
// {
// 	char input[] = "key=value";
//     char **result = get_key_value_pair(input);

// 	printf("Key: %s\n", result[0]);
// 	printf("Value: %s\n", result[1]);
// }