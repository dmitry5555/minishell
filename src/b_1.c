/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:11:44 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/23 14:26:39 by dlariono         ###   ########.fr       */
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

void	ft_cd_2(char *new_path, char *cmd_1, t_list *env)
{
	char	str[10000];

	if (!new_path)
		new_path = cmd_1;
	if (new_path && !chdir(new_path))
	{
		getcwd(str, sizeof(str));
		set_var(&env, "OLDPWD", env_cont(env, "PWD"));
		set_var(&env, "PWD", str);
	}
}

// if CD is single node > CD
// else keep same

void	ft_cd(t_cmd_node *node, t_list *env)
{
	char	*new_path;
	char	*oldpwd;
	char	*not_dir;

	new_path = NULL;
	oldpwd = env_cont(env, "OLDPWD");
	if (!ft_strcmp(node->cmd[1], "(null)"))
		new_path = env_cont(env, "HOME");
	if (!ft_strcmp(node->cmd[1], "-") && !ft_strcmp(oldpwd, "")
		&& !ft_error(ERR_OLDPWD, "", 1))
		return ;
	if (!ft_strcmp(node->cmd[1], "-"))
		new_path = env_cont(env, "OLDPWD");
	else if (access(node->cmd[1], F_OK) != 0
		&& !ft_error(ERR_DIR, node->cmd[1], 1))
		return ;
	not_dir = ft_strjoin(node->cmd[1], "/");
	if (!new_path && (access(not_dir, F_OK) != 0)
		&& !ft_error(ERR_NDIR, node->cmd[1], 1))
	{
		free(not_dir);
		return ;
	}
	free(not_dir);
	ft_cd_2(new_path, node->cmd[1], env);
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
