/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:24:07 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/11 23:26:05 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_here_str(char *doc[2], size_t len, char *del, char *warn)
{
	char	*temp;

	while (g_status != 130 && (!doc[0] || ft_strncmp(doc[0], del, len)
			|| ft_strlen(del) != len))
	{
		temp = doc[1];
		doc[1] = ft_strjoin(doc[1], doc[0]);
		free(temp);
		free(doc[0]);
		doc[0] = readline("> ");
		if (!doc[0])
		{
			printf("%s (wanted `%s\')\n", warn, del);
			break ;
		}
		temp = doc[0];
		doc[0] = ft_strjoin(doc[0], "\n");
		free(temp);
		len = ft_strlen(doc[0]) - 1;
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
		node->in = get_heredoc(doc, del, "warning: heredoc delimited by EOF");
	}
	if (!args[*i] || node->in == -1)
	{
		*i = -1;
		if (node->in != -1)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token", 2);
			g_status = 2;
		}
	}
	return (node);
}
