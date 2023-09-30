# include "minishell.h"

// get cwd - curr.wrk.dir and print it
int ft_pwd(void)
{
	char	cwd[1000000];

	if (getcwd(cwd, 1000000))
	{
		ft_putendl_fd(cwd, 1);
		return(0); // return status
	}
	else
		return(0); // return status
}

void ft_env(t_list *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
}

void	ft_cd(t_cmd_node *node, t_list *env)
{
	char *new_path;
	char *oldpwd;

	// || !strcmp(node->cmd[1], ft_strjoin("~", get_content_by_name(env, "USER") ))
	oldpwd = get_content_by_name(env, "OLDPWD");
	// oldpwd is empty
	if (!ft_strcmp(oldpwd, "") && !ft_strcmp(node->cmd[1], "-"))
	{
		printf("cd: OLDPWD not set\n");
		return ;
	}
	// back to oldpwd
	else if (!ft_strcmp(node->cmd[1], "-"))
	{
		new_path = ft_strdup(get_content_by_name(env, "OLDPWD"));
		printf( "this is back to oldpwd, new_path is [OLDPWD] %s \n", new_path );
	}
	// to home
	else if (!node->cmd[1] || !ft_strcmp(node->cmd[1], get_content_by_name(env, "HOME"))
		|| !ft_strcmp(node->cmd[1], ft_strjoin("~", get_content_by_name(env, "HOME"))))
	{
		printf( "this is [cd] or [cd ~] / [cd ~name] \n" );
		new_path = ft_strdup(get_content_by_name(env, "HOME"));
		printf( "%s\n", node->cmd[1] );
	}
	// random path if have access
	else if (access(node->cmd[1], R_OK) != -1)
	{
		new_path = ft_strdup(node->cmd[1]);
	}
	// if no access
	else if (access(node->cmd[1], R_OK) == -1)
	{
		printf( "No such file or directory %s", node->cmd[1]);
		return ;
	}

	if (new_path) // access(new_path, R_OK)
	{
		set_var(&env, "OLDPWD", get_content_by_name(env, "PWD"));
		set_var(&env, "PWD", new_path);
		new_path = ft_strdup(get_content_by_name(env, "PWD"));
		printf("changed to %s\n", new_path);
		chdir(new_path);
	}

}
