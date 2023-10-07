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

// void ft_env(t_list *env)
// {
// 	while (env)
// 	{
// 		printf("%s=%s\n", env->name, env->content);
// 		env = env->next;
// 	}
// }

void	ft_cd(t_cmd_node *node, t_list *env)
{
	char *new_path;
	char *oldpwd;
	char s[1000];

	// || !strcmp(node->cmd[1], ft_strjoin("~", get_content_by_name(env, "USER") ))
	oldpwd = get_content_by_name(env, "OLDPWD");
	// oldpwd is empty

	// to home !! need to check with ENV cause node->cmd[1] is parsed
	if (!node->cmd[1] || !ft_strcmp(node->cmd[1], get_content_by_name(env, "HOME"))
		|| !ft_strcmp(node->cmd[1], ft_strjoin("~", get_content_by_name(env, "HOME"))))
	{
		printf( "this is [cd] or [cd ~] / [cd ~name] \n" );
		// new_path = ft_strdup(get_content_by_name(env, "HOME"));
		// printf( "%s\n", node->cmd[1] );
		new_path = get_content_by_name(env, "HOME");
	}
	// epand home ~/smth
	// else if () {}

	//remove ./
	else if (node->cmd[0][0] == '.' && node->cmd[0][1] == '/')
	{
		printf("[./] remove one dot \n");
		node->cmd[0][0] = ' ';
	}
	else if (!ft_strcmp(oldpwd, "") && !ft_strcmp(node->cmd[1], "-"))
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

	// random path if have access
	else if (access(node->cmd[1], R_OK) != -1)
		new_path = ft_strdup(node->cmd[1]);
	// if no access
	else if (access(node->cmd[1], R_OK) == -1)
	{
		printf( "No such file or directory %s\n", node->cmd[1]);
		return ;
	}

	if (new_path) // access(new_path, R_OK)
	{
		if (!chdir(new_path))
		{
			getcwd(s, sizeof(s));
			printf("changed to %s\n", new_path);
			set_var(&env, "OLDPWD", get_content_by_name(env, "PWD"));
			set_var(&env, "PWD", s);
		}
		// set_var(&env, "OLDPWD", get_content_by_name(env, "PWD"));
		// set_var(&env, "PWD", new_path);
		// new_path = ft_strdup(get_content_by_name(env, "PWD"));
		// printf("changed to %s\n", new_path);

	}

}


void ft_echo(char **args)
{
	int i;
	int flag_n;

	flag_n = 0;
	i = 1;
	if (nb_args(args) > 1)
	{
		while(args[i] && args[i][0] == '-')
		{
			int j = 1;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				flag_n = 1;
			}
			i++;
		}
		if (!flag_n)
			i--;
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0])
				write(1, " ", 1);
			i++;
		}
	}
	if (!flag_n)
		write(1,"\n",1);
}

void ft_print_env(t_list *env)
{
	if (env != NULL)
	{
		while (env)
		{
			printf("%s=%s\n", env->name, env->content);
			env = env->next;
		}
	}
}

void ft_export()
{
	return ;
}

void ft_exit()
{
	return ;
}

void ft_unset(char *str, t_list *env)
{
	unset_var(&env, str);
}