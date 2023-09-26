/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:36:45 by justindaly        #+#    #+#             */
/*   Updated: 2023/09/26 19:19:43 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status = 0; //add extern

int	get_fd(int oldfd, char *path, int flag1, int flag2)
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flag1) //cannot open file
		ft_error(ERR_DIR, path, 127);
	else if (!flag1 && access(path, R_OK) == -1) //no permission to read
		ft_error(ERR_PERM, path, 126);
	else if (flag1 && access(path, W_OK) == -1 && access(path, F_OK) == 0) //no permission to write
		ft_error(ERR_PERM, path, 126);
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
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

char *get_here_str(char *doc[2], size_t len, char *del, char *warn)
{
	char *temp;
	while (g_status != 130 && (!doc[0] || ft_strncmp(doc[0], del, len) || ft_strlen(del) != len))
	{
		temp = doc[1];
		doc[1] = ft_strjoin(doc[1], doc[0]);
		free(temp);
		free(doc[1]);
		doc[1] = readline("< ");
		if (!doc[0])
		{
			printf("%s (wanted `%s\')\n", warn, del);
			break ;
		}
		temp = doc[0];
		doc[0] = ft_strjoin(doc[0], "\n");
		free(temp);
		len = ft_strlen(doc[0] - 1);
	}
	free(doc[0]);
	return (doc[1]);
}

int	get_heredoc(char *doc[2], char *del, char *warn)
{
	int	fd[2];

	g_status = 0;
	if (pipe(fd) == -1)
	{
		ft_error(ERR_PIPE, NULL, 1);
		return (-1);
	}
	doc[1] = get_here_str(doc, 0, del, warn);
	write(fd[WRITE_END], doc[1], ft_strlen(doc[1]));
	free(doc[1]);
	close(fd[WRITE_END]);
	if (g_status == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}

t_cmd_node	*get_infile_heredoc(t_cmd_node *node, char **args, int *i)
{
	char	*del;
	char	*doc[2];

	del = NULL;
	doc[0] = NULL;
	doc[1] = NULL;
	(*i)++;
	if (args[++(*i)])
	{
		del = args[*i];
		node->in = get_heredoc(doc, del, "minishell: warning: heredoc delimited by EOF");
	}
	if (!args[*i] || node->in == -1)
	{
		*i = -1;
		if (node->in != -1)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
			g_status = 2;
		}
	}
	return(node);
}