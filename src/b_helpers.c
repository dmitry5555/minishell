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

// loop throuh working paths ftom ENV and test if cmd can run
// if ok writes new path to node->path

void ft_find_right_paths(t_cmdlist *cmd_list)
{
	t_cmdlist *current = cmd_list;

	while (current)
	{
		t_cmd_node *node = (t_cmd_node *)current->content;

		int flag = 0;
		char *cmd = node->cmd[0];

		const char* arr[] =
		{
			"/usr/local/bin",
			"/usr/bin",
			"/bin",
			"/usr/sbin",
			"/sbin",
			"/usr/local/munki"
		};

		int total = sizeof(arr) / sizeof(arr[0]);

		while (total--)
		{
			char *tmp1 = ft_strjoin(arr[total], "/");
			char *tmp2 = ft_strjoin(tmp1, cmd);

			if (access(tmp2, X_OK) == 0)
			{
				// Free the old path string
				free(node->path);

				// Allocate memory for the new path and copy it
				node->path = strdup(tmp2);

				// printf("⚪️ FT_FIND_RIGHT_PATH @ b_helpers.c\n");
				// printf("Testing path - [%s]\n", tmp2);
				// printf("Path [%s] is accessible. New path for this node is [%s]\n\n", arr[total], tmp2);
				flag = 1;
			}

			free(tmp1);
			free(tmp2);

			if (flag)
				break;
		}

		current = current->next;
	}
}



// int ft_find_right_path(char *cmd, char *path)
// {
// 	int	flag;
// 	int total;
// 	char *tmp1;
// 	char *tmp2;

// 	// char *cmd = "ls";

// 	const char* arr[] =
// 	{
// 		"/usr/local/bin",
// 		"/usr/bin",
// 		"/bin",
// 		"/usr/sbin",
// 		"/sbin",
// 		"/usr/local/munki"
// 	};

// 	total = sizeof(arr) / sizeof(arr[0]);

// 	flag = 0;
// 	while(total--)
// 	{
// 		tmp1 = ft_strjoin(arr[total],"/");
// 		tmp2 = ft_strjoin(tmp1, cmd);
// 		if (access(tmp2, X_OK) == 0)
// 		{
// 			path = tmp2;
// 			printf("⚪️ FT_FIND_RIGHT_PATH @ b_helpers.c \n	testing path - [%s] \n\n", path);
// 			printf("⚪️ FT_FIND_RIGHT_PATH @ b_helpers.c \n	path [%s] is accessible. new path for this node is [%s] \n\n", arr[total], tmp2);
// 			flag = 1;
// 		}
// 		free(tmp1);
// 		free(tmp2);
// 	}
// 	return(flag);
// }


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