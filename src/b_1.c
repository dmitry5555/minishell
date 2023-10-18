/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:11:44 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/18 18:19:44 by dlariono         ###   ########.fr       */
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
	// home = env_cont(env, "HOME");
	// printf("🍔  node->cmd[1]: %s\n",node->cmd[1]);

	// 1 if cd "" - copy home.  strdup leak  ✅
 	if (!ft_strcmp(node->cmd[1], "(null)"))
	{
		new_path = env_cont(env, "HOME");
		// printf("THAT CASE🛑  node->cmd[1]: %s\n",node->cmd[1]);
	}
	// no OLDPWD ✅
	if (!ft_strcmp(node->cmd[1], "-") && !ft_strcmp(oldpwd, ""))
	{
		ft_error(ERR_OLDPWD, "", 1);
		return ;
	}
	// OLDPWD ✅
	if (!ft_strcmp(node->cmd[1], "-"))
		new_path = env_cont(env, "OLDPWD");
	// no such file or directory ✅
	else if (access(node->cmd[1], F_OK) != 0)
	{
		ft_error(ERR_DIR, node->cmd[1], 1);
		return ;
	}
	// not a directory ✅
	char	*not_dir;
	not_dir = ft_strjoin(node->cmd[1], "/");
	if (!new_path && (access(not_dir, F_OK) != 0))
	{
		ft_error(ERR_NDIR, node->cmd[1], 1);
		free(not_dir);
		return ;
	}
	free(not_dir);
	if (!new_path)
		new_path = node->cmd[1];
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
