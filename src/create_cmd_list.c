/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:26:39 by justindaly        #+#    #+#             */
/*   Updated: 2023/10/02 19:06:40 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_node	*fill_content(t_cmd_node *node, char **args, char **trim_args, int *i)
{
	if (args[*i])
	{
		if (args[*i][0] == '>' && args[*i + 1] && args[*i + 1][0] == '>') //append
			node = get_outfile_append(node, trim_args, i);
		else if (args[*i][0] == '>')
			node = get_outfile(node, trim_args, i);
		else if (args[*i][0] == '<' && args[*i + 1] && args[*i + 1][0] == '<') //heredoc
			node = get_infile_heredoc(node, trim_args, i);
		else if (args[*i][0] == '<')
			node = get_infile(node, trim_args, i);
		else if (args[*i][0] != '|')
			node->cmd = ft_array_extend(node->cmd, trim_args[*i]);
		else
		{
			//error
			*i = -2;
		}
		return (node);
	}
	//error
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

static t_cmdlist	*fill_cmdlst_error(t_cmdlist *cmds, char **args, char **tmp)
{
	ft_cmdlstclear(&cmds, free_cmd_content);
	ft_array_free(&tmp);
	ft_array_free(&args);
	return (NULL);
}

t_cmdlist	*create_cmd_list(char **args, int i)
{
	t_cmdlist	*cmds;
	t_cmdlist	*current_cmd;
	char		**temp_args;
	char		**trimmed_args;

	cmds = NULL;
	trimmed_args = get_trimmed_array(args);
	while (args && args[++i])
	{
		current_cmd = ft_cmdlstlast(cmds);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			if (args[i][0] == '|')
				i++;
			ft_cmdlstadd_back(&cmds, ft_cmdlstnew(init_cmd_node()));
			current_cmd = ft_cmdlstlast(cmds);
		}
		temp_args = args;
		current_cmd->content = fill_content(current_cmd->content, temp_args, trimmed_args, &i);
		if (i < 0)
			return (fill_cmdlst_error(cmds, args, temp_args));
		if (!args[i])
			break ;
	}
	ft_array_free(&trimmed_args);
	ft_array_free(&args);
	return (cmds);
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
