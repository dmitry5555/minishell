/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:11:44 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/16 15:55:40 by dlariono         ###   ########.fr       */
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
	char	s[10000];

	new_path = NULL;
	oldpwd = env_cont(env, "OLDPWD");
	if (!node->cmd[1] || !ft_strcmp(node->cmd[1], env_cont(env, "HOME"))
		|| !ft_strcmp(node->cmd[1], ft_strjoin("~", env_cont(env, "HOME"))))
		new_path = env_cont(env, "HOME");
	else if (node->cmd[0][0] == '.' && node->cmd[0][1] == '/')
		node->cmd[0][0] = ' ';
	else if (!ft_strcmp(oldpwd, "") && !ft_strcmp(node->cmd[1], "-"))
		return ;
	else if (!ft_strcmp(node->cmd[1], "-"))
		new_path = ft_strdup(env_cont(env, "OLDPWD"));
	else if (access(node->cmd[1], R_OK) != -1)
		new_path = ft_strdup(node->cmd[1]);
	else if (access(node->cmd[1], R_OK) == -1)
	{
		ft_error(ERR_DIR, node->cmd[1], 1);
		return ;
	}
	if (new_path && !chdir(new_path))
	{
		getcwd(s, sizeof(s));
		set_var(&env, "OLDPWD", env_cont(env, "PWD"));
		set_var(&env, "PWD", s);
	}
}

int	ft_echo_flag(char *arg)
{
	int	i;
	int	flag;

	i = 2;
	flag = 0;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		flag = 1;
		while (arg[i] && arg[i] != ' ')
		{
			if (arg[i] != 'n')
				flag = 0;
			i++;
		}
	}
	return (flag);
}

int	ft_echo(char **args)
{
	int	arg_start;
	int	flag;

	flag = 0;
	arg_start = 1;
	if (!args[arg_start])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	flag = ft_echo_flag(args[arg_start]);
	arg_start += flag;
	while (args[arg_start])
	{
		ft_putstr_fd(args[arg_start], 1);
		if (args[arg_start + 1] && args[arg_start][0])
			write(1, " ", 1);
		arg_start++;
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
