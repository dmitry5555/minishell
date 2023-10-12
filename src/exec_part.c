/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:12:08 by dlariono          #+#    #+#             */
/*   Updated: 2023/10/12 17:14:01 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

// print cmd list for testing
void	print_cmd_list(t_cmdlist *cmd_list)
{
	t_cmd_node	*node;

	if (cmd_list != NULL)
	{
		while (cmd_list)
		{
			node = (t_cmd_node *)cmd_list->content;
			for (int i = 0; node->cmd[i] != NULL; i++)
				printf("cmd[%d] = %s ", i, node->cmd[i]);
			printf("\n");
			printf("Input File: %d\n", node->in);
			printf("Output File: %d\n", node->out);
			printf("---------\n");
			cmd_list = cmd_list->next;
		}
	}
}

int	run_builtin(t_cmdlist *cmd_list, t_list *env, int *is_exit)
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
			ft_unset(node, env);
		else if (!ft_strcmp(node->cmd[0], "exit"))
			g_status = ft_exit(cmd_list, env, is_exit);
		if (!ft_strcmp(node->cmd[0], "cd")
			|| !ft_strcmp(node->cmd[0], "export")
			|| !ft_strcmp(node->cmd[0], "unset")
			|| !ft_strcmp(node->cmd[0], "exit"))
			return (1);
	}
	return (0);
}

void	run_single(t_cmdlist *cmd_list, t_list *env, int fd[2])
{
	t_cmd_node	*node;
	pid_t		pid;

	node = (t_cmd_node *)cmd_list->content;
	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
	}
	else if (!pid)
	{
		// child redirection
		if (node->in != STDIN_FILENO)
		{
			dup2(node->in, STDIN_FILENO);
			close(node->in);
		}
		if (node->out != STDOUT_FILENO)
		{
			dup2(node->out, STDOUT_FILENO);
			close(node->out);
		}
		else if (cmd_list->next)
			dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		// END child redirection
		close(fd[READ_END]);
		// child process child_builtin
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);

		if (!ft_strcmp(node->cmd[0], "echo"))
			g_status = ft_echo(node->cmd);
		else if (!ft_strcmp(node->cmd[0], "pwd"))
			g_status = ft_pwd();
		else if (!ft_strcmp(node->cmd[0], "env"))
			g_status = ft_env_print(env, 0);
		// if (!ft_strcmp(node->cmd[0], "echo") || !ft_strcmp(node->cmd[0], "pwd") || !ft_strcmp(node->cmd[0], "env"))
		// 	exit(g_status);
		else if (!ft_is_builtin(node->cmd[0]))
		{
			execve(node->path, node->cmd, NULL);
			ft_error(ERR_CMD, node->cmd[0], 127); //add error message if cmd doesn't execute
			ft_cmdlstclear(&cmd_list, free_cmd_content); //clear list if error to prevent leak
		}
		ft_cmdlstclear(&cmd_list, free_cmd_content);
		exit(g_status);
	}
}

void	pre_run_single(t_cmdlist *cmd_list, t_list *env)
{
	int	fd[2];
	pipe(fd);
	// check to fork
	// exec fork - run_single


	if (!ft_strcmp(((t_cmd_node *)cmd_list->content)->cmd[0], "./minishell"))
		if (!access("./minishell", X_OK))
			change_shlvl(env, 1);
	ft_putstr_fd(((t_cmd_node *)cmd_list->content)->path ,1);
	ft_putstr_fd("\n" ,1);
	run_single(cmd_list, env, fd);

	// after
	// close(fd[READ_END]);
	close(fd[WRITE_END]);
	if (cmd_list->next && !((t_cmd_node *)cmd_list->next->content)->in) // !!!
		((t_cmd_node *)cmd_list->next->content)->in = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_cmd_node *)cmd_list->content)->in > 2)
		close(((t_cmd_node *)cmd_list->content)->in);
	if (((t_cmd_node *)cmd_list->content)->out > 2)
		close(((t_cmd_node *)cmd_list->content)->out);
}

int	run_multiple(t_cmdlist *cmd_list, t_list *env, int *is_exit)
{
	while (cmd_list)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (!run_builtin(cmd_list, env, is_exit))
			pre_run_single(cmd_list, env);
		cmd_list = cmd_list->next;
	}

	return (g_status);

}

void	exec_all(char *out, t_list *env)
{
	t_cmdlist	*cmd_list;
	char		**args;
	int			cmds_num;
	int			is_exit;

	cmd_list = NULL;
	if (out[0] != '\0')
		add_history(out);
	is_exit = 0;
	args = ft_split_cmds(out, " ");
	free(out);
	if (!args)
		ft_error(ERR_QUOTE, NULL, 1);
	if (args)
	{
		cmd_list = create_cmd_list(final_split(args, env), -1);
		if (!cmd_list)
			return ;
		ft_find_right_paths(cmd_list);
		cmds_num = ft_cmdlstsize(cmd_list);
		g_status = run_multiple(cmd_list, env, &is_exit);
		while (0 < cmds_num--)
		{
			waitpid(-1, &g_status, 0);
			//printf("gstatus = %d\n", g_status);
		}

		if (!is_exit && g_status == 13)
			g_status = 0;
		if (g_status > 255)
			g_status = g_status / 255;
		if (args && is_exit)
		{
			ft_cmdlstclear(&cmd_list, free_cmd_content);
			exit(g_status);
		}

		// end parse args
		// return (1);
	}
	ft_cmdlstclear(&cmd_list, free_cmd_content);
	//return (cmd_list);
}

int	main(int argc, char *argv[], char **env)
{
	t_list		*env_list;
	char		*out;

	env_list = ft_env_parser(env);
	while (1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		out = readline("guest@minishell $ ");
		exec_all(out, env_list);
	}
	exit(g_status);
}