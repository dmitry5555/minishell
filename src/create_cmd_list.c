/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justindaly <justindaly@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:26:39 by justindaly        #+#    #+#             */
/*   Updated: 2023/09/07 19:10:30 by justindaly       ###   ########.fr       */
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

static char *rm_quotes(char *str)
{
	int 	len;
	char	*trimmed;
	int		i;

	i = 0;
	len = ft_strlen(str);
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '"' && str[len - 1] == '"'))
	{
		trimmed = malloc(sizeof(char) * (len - 2 + 1));
		if (!trimmed)
			return NULL;
		while (++i < len - 1)
			trimmed[i - 1] = str[i];
		trimmed[i - 1] = '\0';
		return (trimmed);
	}
	else
		return (str);
}

static char	**get_trimmed(char **args)
{
	char	**tmp_array;
	char	*trimmed;
	int		j;

	j = -1;
	tmp_array = ft_dup_array(args);
	while (tmp_array && tmp_array[++j])
	{
		trimmed = rm_quotes(tmp_array[j]);
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
	ft_array_free(tmp);
	ft_array_free(args);
	return (NULL);
}

t_cmdlist	*create_cmd_list(char **args, int i)
{
	t_cmdlist	*cmds;
	t_cmdlist	*current_cmd;
	char		**temp_args;
	char		**trimmed_args;

	cmds = NULL;
	trimmed_args = get_trimmed(args);
	while (args[++i])
	{
		current_cmd = ft_cmdlstlast(cmds);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			if (args[i][0] == '|')
				i += 1;
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
	ft_array_free(trimmed_args);
	ft_array_free(args);
	return (cmds);
}

// int main()
// {
//     char *array[] = {
//         "echo",
//         "Hello,",
//         "world!",
//         ">", "output.txt",
//         "|",
//         "grep", "world",
//         NULL
//     };

//     // Create a command list from the array
// 	t_cmdlist *cmdlist;
	
// 	cmdlist = ft_cmdlstnew(init_cmd_node());

//     // Check if the command list was created successfully
//     if (cmdlist != NULL) 
// 	{
//         // Traverse the command list and print the commands
//         t_cmdlist *current = cmdlist;
//         while (current != NULL) {
//             t_cmd_node *node = (t_cmd_node *)current->content;
//             printf("Command: ");
//             for (int i = 0; node->cmd[i] != NULL; i++) {
//                 printf("%s ", node->cmd[i]);
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