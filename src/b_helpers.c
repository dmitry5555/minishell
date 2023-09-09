# include "minishell.h"


int ft_is_builtin(char *str)
{
	int	size;

	// char *test = "echo";
	const char* b_in[] =
	{
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
	};

	size = sizeof(b_in) / sizeof(b_in[0]);
	while(size--)
	{
		if (!ft_strcmp(b_in[size], str))
		{
			// printf("%s is builtin \n",str);
			return(1);
		}
	}
	return(0);
}

// void ft_find_right_path(t_list **t_cmd_node)

char *ft_find_right_path(char *cmd)
{
	int	i;
	int total;
	char *tmp1;
	char *tmp2;

	// char *cmd = "ls";

	const char* arr[] =
	{
		"/usr/local/bin",
		"/usr/bin",
		"/bin",
		"/usr/sbin",
		"/sbin",
		"/usr/local/munki"
	};

	total = sizeof(arr) / sizeof(arr[0]);

	// split PATH string to arr using ft_sub_create_array
	// check each PATH - array element with access

	while(total--)
	{
		tmp1 = ft_strjoin(arr[total],"/");
		tmp2 = ft_strjoin(tmp1, cmd);
		// free(tmp1);

		if (access(tmp2, X_OK) == 0)
		{
			// free(tmp1);
			// free(tmp2);
			// ft_array_free(arr);
			printf("FT_FIND_RIGHT_PATH @ b_helpers.c: \n	path %s is accessible %s \n\n", arr[total], tmp2);
			//printf("%s is accessible \n", ft_strjoin(ft_strjoin(arr[total],"/"), cmd));
			// return(tmp2);
		}
		else
		{
			// free(tmp1);
			// free(tmp2);
		//	printf("%s is not accessible \n", ft_strjoin(ft_strjoin(arr[total],"/"), cmd));
		}
		// total--;
		free(tmp1);
		free(tmp2);
	}

	// if (access("/usr/local/munki/ls", X_OK) == 0)
	// 	printf("good path");
	// const char* executable = "/usr/local/munki";

	// Check if the executable can be accessed
	// if (access(executable, X_OK) == 0) {
	//     printf("%s is accessible\n", executable);
	// } else {
	//     printf("%s is not accessible\n", executable);
	// }

	return(0);
}

// int main()
// {
// 	// char 		**paths;
// 	// t_cmd_node	*node;

// 	// node = malloc(sizeof(t_cmd_node));

// 	// node->cmd = malloc(2 * sizeof(char *));

// 	// node->cmd[0] = ft_strdup("test1");
// 	// node->cmd[1] = ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");

// 	// paths = ft_sub_create_array(node->cmd[1], ":", 6);
// 	// write(1,&paths[1][1],1);

// 	ft_find_right_path();
// 	ft_is_builtin();
// }