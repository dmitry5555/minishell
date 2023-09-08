/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justindaly <justindaly@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:36:45 by justindaly        #+#    #+#             */
/*   Updated: 2023/09/07 19:29:02 by justindaly       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_fd(int oldfd, char *path, int flag1, int flag2)
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flag1) //cannot open file
		printf("No such file or directory\n");
		//error function
	else if (!flag1 && access(path, R_OK) == -1) //no permission to read
		printf("No permission to read\n");
		//error function
	else if (flag1 && access(path, W_OK) == -1 && access(path, F_OK) == 0) //no permission to write
		printf("No permission to write\n");
		//error function
	if (flag1 && flag2) //>>
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flag1 && !flag2) //>
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flag1 && oldfd != -1) //< <<
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_cmd_node	*get_outfile(t_cmd_node *node, char **args, int *i)
{
	int		flag1;
	int		flag2;

	flag1 = 1; //output mode
	flag2 = 0; //regular write, no append
	(*i)++;
	if (args[*i])
		node->out = get_fd(node->out, args[*i], flag1, flag2);
	if (!args[*i] || node->out == -1)
	{
		*i = -1;
		if (node->out != -1)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
			//g_status = 2;
		}
		//else
			//g_status = 1;
	}
	return (node);
}

t_cmd_node	*get_outfile_append(t_cmd_node *node, char **args, int *i)
{
	int		flag1;
	int		flag2;

	flag1 = 1; //output mode
	flag2 = 1; //append
	(*i)++;
	if (args[++(*i)])
		node->out = get_fd(node->out, args[*i], flag1, flag2);
	if (!args[*i] || node->out == -1)
	{
		*i = -1;
		if (node->out != -1)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
			//g_status = 2;
		}
		//else
			//g_status = 1;
	}
	return (node);
}

t_cmd_node	*get_infile(t_cmd_node *node, char **args, int *i)
{
	int		flag1;
	int		flag2;

	flag1 = 0; //input mode
	flag2 = 0; //not used
	(*i)++;
	if (args[*i])
		node->in = get_fd(node->in, args[*i], flag1, flag2);
	if (!args[*i] || node->in == -1)
	{
		*i = -1;
		if (node->in != -1)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
			//g_status = 2;
		}
		//else
			//g_status = 1;
	}
	return (node);
}

t_cmd_node	*get_infile_heredoc(t_cmd_node *node, char **args, int *i)
{
	return(node);
	//heredoc function
}