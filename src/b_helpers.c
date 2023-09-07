# include "minishell.h"


void ft_is_builtin()
{
	int	size;

	char *test = "echo";
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
		if (!ft_strcmp(b_in[size], test))
			printf("%s is builtin \n",test);

	}
}

// void ft_find_right_path(t_list **t_cmd_node)
void ft_find_right_path()
{
	int	i;
	int total;

	char *cmd = "ls";

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
		if (access(ft_strjoin(ft_strjoin(arr[total],"/"), cmd), X_OK) == 0)
			printf("%s is accessible \n", ft_strjoin(ft_strjoin(arr[total],"/"), cmd));
		else
			printf("%s is not accessible \n", ft_strjoin(ft_strjoin(arr[total],"/"), cmd));
		// total--;

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