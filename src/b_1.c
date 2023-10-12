/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:11:44 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/12 19:05:58 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export starts with letter

int	ft_pwd(void)
{
	char	cwd[1000000];

	if (getcwd(cwd, 1000000))
		ft_putendl_fd(cwd, 1);
	return (0);
}

// if CD is single node > CD
// else keep same

void	ft_cd(t_cmd_node *node, t_list *env)
{
	char	*new_path;
	char	*oldpwd;
	char	s[1000];

	oldpwd = env_cont(env, "OLDPWD");
	if (!node->cmd[1] || !ft_strcmp(node->cmd[1], env_cont(env, "HOME"))
		|| !ft_strcmp(node->cmd[1], ft_strjoin("~", env_cont(env, "HOME"))))
	{
		printf("this is [cd] or [cd ~] / [cd ~name] \n");
		// new_path = ft_strdup(env_cont(env, "HOME"));
		// printf( "%s\n", node->cmd[1] );
		new_path = env_cont(env, "HOME");
	}

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
		new_path = ft_strdup(env_cont(env, "OLDPWD"));
		printf("this is back to oldpwd, new_path is [OLDPWD] %s \n", new_path);
	}

	// random path if have access
	else if (access(node->cmd[1], R_OK) != -1)
		new_path = ft_strdup(node->cmd[1]);
	// if no access
	else if (access(node->cmd[1], R_OK) == -1)
	{
		printf("No such file or directory %s\n", node->cmd[1]);
		return ;
	}

	// if have access && dir changed OK
	if (new_path && !chdir(new_path))
	{
		printf("executing cd \n");
		getcwd(s, sizeof(s));
		printf("changed to %s\n", new_path);
		set_var(&env, "OLDPWD", env_cont(env, "PWD"));
		set_var(&env, "PWD", s);
	}
	// set_var(&env, "OLDPWD", env_cont(env, "PWD"));
	// set_var(&env, "PWD", new_path);
	// new_path = ft_strdup(env_cont(env, "PWD"));
	// printf("changed to %s\n", new_path);

}

int	ft_echo(char **args)
{
	int	arg_start;
	int	flag;
	int	i;

	i = 2;
	flag = 0;
	arg_start = 1;
	if (!args[arg_start])
		return (0);
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
	while (args[arg_start])
	{
		ft_putstr_fd(args[arg_start], 1);
		if (args[arg_start + 1] && args[arg_start][0])
			write(1," ",1);
		arg_start++;
	}
	if (!flag)
		write(1,"\n",1);
	return (0);
}


int	ft_env_print(t_list *env, int is_export)
{
	if (env != NULL)
	{
		while (env)
		{
			if (is_export && env->name)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(env->name, 1);
				if (env->content)
				{
					ft_putstr_fd("=\"", 1);
					ft_putstr_fd(env->content, 1);
					ft_putstr_fd("\"", 1);
				}
				ft_putstr_fd("\n", 1);
			}
			else if (env->content)
			{
				ft_putstr_fd(env->name, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd(env->content, 1);
				ft_putstr_fd("\n", 1);
			}
			env = env->next;
		}
	}
	return (0);
}

int	check_exp_var(char *str)
{
	int	i;

	i = 0;
	if (('a' <= str[0] && str[0] <= 'z') || ('A' <= str[0] && str[0] <= 'Z'))
	{
		while (str[++i])
			if (!('a' <= str[i] && str[i] <= 'z')
				&& !('A' <= str[i] && str[i] <= 'Z')
				&& !('1' <= str[i] && str[i] <= '9'))
				return (1);
		return (0);
	}
	return (1);
}

