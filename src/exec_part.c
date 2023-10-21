/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:12:08 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/21 18:35:40 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_no_access(t_cmd_node	*node)
{
	char	*not_dir;

	if (node->cmd[0][0] == '.' && !node->cmd[0][1]
		&& !ft_error(ERR_FNARG, node->cmd[0], 2))
		return (1);
	not_dir = ft_strjoin(node->cmd[0], "/");
	if (access(not_dir, F_OK) == 0 && access(node->cmd[0], F_OK) == 0)
	{
		ft_error(ERR_ISDIR, node->cmd[0], 126);
		free(not_dir);
		return (1);
	}
	free(not_dir);
	if (access(node->path, F_OK) == -1 && ft_strchr(node->path, '/'))
	{
		ft_error(ERR_DIR, node->cmd[0], 127);
		return (1);
	}
	if (!access(node->path, F_OK) && access(node->path, X_OK != 0)
		&& ft_error(ERR_PERM, node->cmd[0], 126))
		ft_error(ERR_PERM, node->cmd[0], 126);
	if (access(node->path, X_OK) != 0 && !ft_error(ERR_CMD, node->cmd[0], 127))
		return (1);
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
		if (!ft_no_access(node))
		{
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
