/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:10:00 by jdaly             #+#    #+#             */
/*   Updated: 2023/09/27 16:39:12 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **final_split(char **args, t_list *envlist)
{
    expand_all(args, envlist);
    args = ft_subsplit(args, "<|>", -1);
    return (args);
}

t_cmdlist	*check_args(char *out, t_list *envlist)
{
	char **args;
    t_cmdlist *cmd_list;

    cmd_list = NULL;
	if (!out)
	{
		printf("exit\n");
		return NULL;
	}
	if (out[0] != '\0')
		add_history(out);
	args = ft_split_cmds(out);
    if (!args)
        ft_error(ERR_QUOTE, NULL, 2);
    if (args)
    {
        printf("AFTER FT_SPLIT_CMDS:\n");
        ft_print_array(args);
    }
	free(out);
    if (args)
        cmd_list = create_cmd_list(final_split(args, envlist), -1);
    if (cmd_list != NULL)
	{
        // Traverse the command list and print the commands
        t_cmdlist *current = cmd_list;
        while (current != NULL) {
            t_cmd_node *node = (t_cmd_node *)current->content;
            //printf("Command: ");
            for (int i = 0; node->cmd[i] != NULL; i++) {
                printf("cmd[%d] = %s ", i, node->cmd[i]);
            }
            printf("\n");
            printf("Input File: %d\n", node->in);
            printf("Output File: %d\n", node->out);
            printf("---------\n");

            current = current->next;
        }
    }
	return (cmd_list);
    // ft_cmdlstclear(&cmd_list, free_cmd_content);

}

// // 2. create tokens

// prompt loop function
int	main(int argc, char *argv[])
{
	// 1. get username
	// 2. get home directory
	// 3. display prompt string and wait for input
	char	*prompt;
	char	*out;
    t_list  *envlist = ft_env();
	// char	**array;
	// int		wordcount;
	// char	space = ' ';
	(void)argc;
	(void)argv;
	t_cmdlist *cmd_list;
	t_cmd_node *node;

	// print_cmd_list(cmd_list);
	cmd_list = NULL;
	out = NULL;
	prompt = "jdaly@minishell$ ";
	while (1)
	{
		out = readline(prompt);
// 		//cmd_list = check_args(out, envlist);
// 		ft_find_right_paths(cmd_list);
// 		if (cmd_list != NULL)
// 		{
// // 		// Traverse the command list and print the commands
// 			t_cmdlist *current = cmd_list;
// 			while (cmd_list) {
//  			node = cmd_list->content;

// // 			// for (int i = 0; node->cmd[i] != NULL; i++)
// // 			// 	printf("node[%d] = %s ", i, node->cmd[i]);
// // 			// // printf("\n");
// // 			// printf("Input File: %d\n", node->in);
// // 			// printf("Output File: %d\n", node->out);
// // 			// printf("---------\n");

//  			exec_cmd(cmd_list);
//  			cmd_list = cmd_list->next;
// 			}
// 			ft_cmdlstclear(&cmd_list, free_cmd_content);
//  		}

// 		// Free the memory allocated for the command list


		// wordcount = ft_count_words(out);
		// printf("wordcount = %d\\n", wordcount);
		// array = ft_create_array(out, wordcount);
		// print_array(array);
		free(out);

	}
}