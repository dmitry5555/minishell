/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:12:08 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/13 17:13:06 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // print cmd list for testing
// void	print_cmd_list(t_cmdlist *cmd_list)
// {
// 	t_cmd_node	*node;

// 	if (cmd_list != NULL)
// 	{
// 		while (cmd_list)
// 		{
// 			node = (t_cmd_node *)cmd_list->content;
// 			for (int i = 0; node->cmd[i] != NULL; i++)
// 				printf("cmd[%d] = %s ", i, node->cmd[i]);
// 			printf("\n");
// 			printf("Input File: %d\n", node->in);
// 			printf("Output File: %d\n", node->out);
// 			printf("---------\n");
// 			cmd_list = cmd_list->next;
// 		}
// 	}
// }

int	ft_is_dir(char *cmd)
{
	int	i;
	int	dot;
	int	slash;

	i = 0;
	dot = 0;
	slash = 0;
	while (cmd[i])
	{
		if (cmd[i] == 46)
			dot++;
		if (cmd[i] == 47)
		{
			slash++;
			if (dot < 3)
				dot = 0;
		}
		if (cmd[i] != 47 && cmd[i] != 46)
			return (0);
		i++;
	}
	if (dot < 3 && 0 < slash)
		return (1);
	return (0);
}

int	ft_no_access(char *cmd, char *path)
{
	(void)path;

	if (ft_is_dir(cmd))
	{
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": is a directory\n", 1);
		return (1);
	}
	else if (access(path, F_OK) != 0)
	{
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		return (1);
	}
	else if (access(path, X_OK) != 0)
	{
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": Permission denied\n", 1);
		return (1);
	}
	return (0);
}


int	run_builtin(t_cmdlist *cmd_list, t_list *env, int *is_exit, int ncmds)
{
	t_cmd_node	*node;

	node = (t_cmd_node *)cmd_list->content;
	if (!cmd_list->next)
	{
		if (!ft_strcmp(node->cmd[0], "cd"))
			ft_cd(node, env);
		else if (!ft_strcmp(node->cmd[0], "export"))
			ft_export(node, env);
		else if (!ft_strcmp(node->cmd[0], "unset"))
			ft_unset(node, &env);
		else if (!ft_strcmp(node->cmd[0], "exit") && ncmds == 1)
			g_status = ft_exit(cmd_list, is_exit);
		if (!ft_strcmp(node->cmd[0], "cd")
			|| !ft_strcmp(node->cmd[0], "export")
			|| !ft_strcmp(node->cmd[0], "unset")
			|| !ft_strcmp(node->cmd[0], "exit"))
			return (1);
	}
	return (0);
}

void	run_single_exec(t_cmdlist *cmd_list, t_list *env)
{
	t_cmd_node	*node;

	node = (t_cmd_node *)cmd_list->content;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!ft_strcmp(node->cmd[0], "echo"))
		g_status = ft_echo(node->cmd);
	else if (!ft_strcmp(node->cmd[0], "pwd"))
		g_status = ft_pwd();
	else if (!ft_strcmp(node->cmd[0], "env"))
		g_status = ft_env_print(env, 0);
	else if (!ft_is_builtin(node->cmd[0]))
	{
		printf("cmd name [%s] path [%s]\n",node->cmd[0] , node->path);
		if (!ft_no_access(node->cmd[0], node->path))
		{
			printf("runnning\n");
			execve(node->path, node->cmd, ft_env_to_arr(env));
			ft_error(ERR_CMD, node->cmd[0], 127);
		}
		ft_cmdlstclear(&cmd_list, free_cmd_content);
	}
	ft_cmdlstclear(&cmd_list, free_cmd_content);
	exit(g_status);
}

void	run_single(t_cmdlist *cmd_list, t_list *env, int fd[2])
{
	pid_t		pid;

	pid = fork();
	if (pid < 0 && !close(fd[READ_END]))
		close(fd[WRITE_END]);
	else if (!pid)
	{
		if (((t_cmd_node *)cmd_list->content)->in != STDIN_FILENO)
		{
			dup2(((t_cmd_node *)cmd_list->content)->in, STDIN_FILENO);
			close(((t_cmd_node *)cmd_list->content)->in);
		}
		if (((t_cmd_node *)cmd_list->content)->out != STDOUT_FILENO)
		{
			dup2(((t_cmd_node *)cmd_list->content)->out, STDOUT_FILENO);
			close(((t_cmd_node *)cmd_list->content)->out);
		}
		else if (cmd_list->next)
			dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		close(fd[READ_END]);
		run_single_exec(cmd_list, env);
	}
}

void	pre_run_single(t_cmdlist *cmd_list, t_list *env)
{
	int	fd[2];

	pipe(fd);
	// if (!ft_strcmp(((t_cmd_node *)cmd_list->content)->cmd[0], "./minishell"))
	// 	if (!access("./minishell", X_OK))
	// 		change_shlvl(env, 1);
	ft_putstr_fd("this is a path: ", 1);
	ft_putstr_fd(((t_cmd_node *)cmd_list->content)->path, 1);
	ft_putstr_fd("\n",1);
	run_single(cmd_list, env, fd);
	close(fd[WRITE_END]);
	if (cmd_list->next && !((t_cmd_node *)cmd_list->next->content)->in)
		((t_cmd_node *)cmd_list->next->content)->in = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_cmd_node *)cmd_list->content)->in > 2)
		close(((t_cmd_node *)cmd_list->content)->in);
	if (((t_cmd_node *)cmd_list->content)->out > 2)
		close(((t_cmd_node *)cmd_list->content)->out);
}
