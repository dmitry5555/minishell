# include "minishell.h"
//ft_lstadd_back

void ft_if_builtin(t_list **t_cmd_node)
{
	// split PATH string to arr

	// check each PATH with access

	// while()
	// {
	// 	if (access(exec_path, X_OK) == 0)
	// 		printf("builtin");
	// }
}

// int main()
// {
// 	t_cmd_node	*node;

// 	node = malloc(sizeof(t_cmd_node));

// 	node->cmd = malloc(2 * sizeof(char *));

// 	node->cmd[0] = ft_strdup("test1");
// 	node->cmd[1] = ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");

// 	ft_sub_create_array(node->cmd[1], ':', 6);
// 	// printf("%s", node->cmd[1]);

// 	// while()
// }