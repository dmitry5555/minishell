/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:26:39 by justindaly        #+#    #+#             */
/*   Updated: 2023/10/12 00:50:30 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_node	*fill_content(t_cmd_node *node, char **args, char **t_args, int *i)
{
	if (args[*i])
	{
		if (args[*i][0] == '>' && args[*i + 1] && args[*i + 1][0] == '>')
			node = get_outfile_append(node, t_args, i);
		else if (args[*i][0] == '>')
			node = get_outfile(node, t_args, i);
		else if (args[*i][0] == '<' && args[*i + 1] && args[*i + 1][0] == '<')
			node = get_infile_heredoc(node, t_args, i);
		else if (args[*i][0] == '<')
			node = get_infile(node, t_args, i);
		else if (args[*i][0] != '|')
			node->cmd = ft_array_extend(node->cmd, t_args[*i]);
		else
		{
			ft_error(ERR_PIPESYN, NULL, 2);
			*i = -2;
		}
		return (node);
	}
	ft_error(ERR_PIPESYN, NULL, 2);
	*i = -2;
	return (node);
}

static int	num_quotes_to_trim(char const *s1)
{
	int	qcount;
	int	i;
	int	in_dq;
	int	in_sq;

	i = 0;
	qcount = 0;
	in_dq = 0;
	in_sq = 0;
	while (s1 && s1[i])
	{
		in_sq = (in_sq + (!in_dq && s1[i] == '\'')) % 2;
		in_dq = (in_dq + (!in_sq && s1[i] == '\"')) % 2;
		if ((s1[i] == '\"' && !in_sq) || (s1[i] == '\'' && !in_dq))
			qcount++;
		i++;
	}
	if (in_sq || in_dq)
		return (-1);
	return (qcount);
}

//returns the string with quote characters trimmed
char	*ft_trim_quotes(char const *s1, int in_sq, int in_dq)
{
	int		qcount;
	int		i;
	int		j;
	char	*trimmed;

	j = -1;
	i = 0;
	qcount = num_quotes_to_trim(s1);
	if (!s1 || qcount == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(s1) - qcount + 1));
	if (!trimmed)
		return (NULL);
	while (s1[i])
	{
		in_sq = (in_sq + (!in_dq && s1[i] == '\'')) % 2;
		in_dq = (in_dq + (!in_sq && s1[i] == '\"')) % 2;
		if ((s1[i] != '\"' || in_sq) && (s1[i] != '\'' || in_dq) \
			&& ++j >= 0)
			trimmed[j] = s1[i];
		i++;
	}
	trimmed[++j] = '\0';
	return (trimmed);
}

char	**get_trimmed_array(char **args)
{
	char	**tmp_array;
	char	*trimmed;
	int		j;

	j = -1;
	tmp_array = ft_dup_array(args);
	while (tmp_array && tmp_array[++j])
	{
		trimmed = ft_trim_quotes(tmp_array[j], 0, 0);
		if (trimmed != tmp_array[j])
		{
			free(tmp_array[j]);
			tmp_array[j] = trimmed;
		}
	}
	return (tmp_array);
}

/*	cmd[0] = command list;
	cmd[0] = current command;
	t_args[0] = temp;
	t_args[1] = trimmed args */
t_cmdlist	*create_cmd_list(char **args, int i)
{
	t_cmdlist	*cmds[2];
	char		**tmp[2];

	cmds[0] = NULL;
	tmp[1] = get_trimmed_array(args);
	while (args && args[++i])
	{
		cmds[1] = ft_cmdlstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			if (args[i][0] == '|')
				i++;
			ft_cmdlstadd_back(&cmds[0], ft_cmdlstnew(init_cmd_node()));
			cmds[1] = ft_cmdlstlast(cmds[0]);
		}
		tmp[0] = args;
		cmds[1]->content = fill_content(cmds[1]->content, tmp[0], tmp[1], &i);
		if (i < 0)
			return (fill_cmdlst_error(cmds[0], args, tmp[1]));
		if (!args[i])
			break ;
	}
	ft_array_free(&tmp[1]);
	ft_array_free(&args);
	return (cmds[0]);
}

// int main()
// {
//     char **array = malloc(sizeof(char *) * 6);
//     array[0] = strdup("echo");
// 	array[1] = strdup("string1");
//     array[2] = strdup("|");
//     array[3] = strdup("grep");
// 	array[4] = strdup("string2");
//     array[5] = NULL;

//     // Create a command list from the array
// 	t_cmdlist *cmdlist;

// 	cmdlist = NULL;
// 	cmdlist = create_cmd_list(array, -1);

//     //Check if the command list was created successfully
//     if (cmdlist != NULL)
// 	{
//         // Traverse the command list and print the commands
//         t_cmdlist *current = cmdlist;
//         while (current != NULL) {
//             t_cmd_node *node = (t_cmd_node *)current->content;
//             //printf("Command: ");
//             for (int i = 0; node->cmd[i] != NULL; i++) {
//                 printf("cmd[%d] = %s ", i, node->cmd[i]);
//             }
//             printf("\n");
//             printf("Input File: %d\n", node->in);
//             printf("Output File: %d\n", node->out);
//             printf("---------\n");

//             current = current->next;
//         }

//         // Free the memory allocated for the command list
//         ft_cmdlstclear(&cmdlist, free_cmd_content);
//     }
// 	else
// 	{
//         printf("Failed to create the command list.\n");
//     }

//     return 0;
// }
