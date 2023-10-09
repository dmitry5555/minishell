# include "minishell.h"

// export starts with letter

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

// if CD is single node > CD
// else keep same

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

	if (new_path && !chdir(new_path)) // if have access && dir changed OK
	{
		printf("executing cd \n");
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


void ft_echo(char **args)
{
	int arg_start;
	int flag;
	int i;

	i = 2;
	flag = 0;
	arg_start = 1;
	if (!args[arg_start])
		return ;
	if (args[arg_start][0] == '-' && args[arg_start][1] == 'n')
	{
		flag = 1;
		while (args[arg_start][i] && args[arg_start][i] != ' ')
		{
			if (args[arg_start][i] != 'n')
				flag = 0;
			i++;
		}
	}
	arg_start += flag;
	while(args[arg_start])
	{
		ft_putstr_fd(args[arg_start], 1);
		if (args[arg_start + 1] && args[arg_start][0])
			write(1," ",1);
		arg_start++;
	}
	if (!flag)
		write(1,"\n",1);
}


// void ft_echo(char **args)
// {
// 	int i;
// 	int flag_n;

// 	flag_n = 0;
// 	i = 1;
// 	if (nb_args(args) > 1)
// 	{
// 		while(args[i] && args[i][0] == '-')
// 		{
// 			int j = 1;
// 			while (args[i][j] == 'n')
// 				j++;
// 			if (args[i][j] == '\0')
// 			{
// 				flag_n = 1;
// 			}
// 			i++;
// 		}
// 		if (!flag_n)
// 			i--;
// 		while (args[i])
// 		{
// 			ft_putstr_fd(args[i], 1);
// 			if (args[i + 1] && args[i][0])
// 				write(1, " ", 1);
// 			i++;
// 		}
// 	}
// 	if (!flag_n)
// 		write(1,"\n",1);
// }

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


void ft_export(t_cmd_node *cmd, t_list *env)
{
	int i;
	int j;
	int flag;
	char	*c;

	i = 1;
	while(cmd->cmd[i])
	{
		j = 0;
		flag = 0;
		if (get_key_value_pair(cmd->cmd[i])[1]) // if have arg "var=1"
		{
			// c = get_key_value_pair(cmd->cmd[i])[0][0];
			// if ( ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') )
			// {
			// 	while (get_key_value_pair(cmd->cmd[i])[0][j])
			// 	{
			// 		c = get_key_value_pair(cmd->cmd[i])[0][j];
			// 		if (!('0' <= c && c <= '9') || !('a' <= c && c <= 'z') || !('A' <= c && c <= 'Z'))
			// 			flag = 1;
			// 		j++;
			// 	}
				set_var(&env, get_key_value_pair(cmd->cmd[i])[0], get_key_value_pair(cmd->cmd[i])[1]);

		}
		i++;
	}
}

// change shlvl on new minishell / exit
void change_shlvl(t_list *env, int inc)
{
	while(env)
	{
		if (!ft_strcmp(env->name, "SHLVL"))
			env->content = ft_itoa(ft_atoi(env->content) + inc);
		env = env->next;
	}
}

void ft_exit(t_cmd_node *cmd, t_list *env)
{
	ft_putstr_fd("exit. bye bye\n",1);
	exit(1);
	return ;
}

void ft_unset(char *str, t_list *env)
{
	unset_var(&env, str);
}