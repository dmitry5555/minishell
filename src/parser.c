/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:10:00 by jdaly             #+#    #+#             */
/*   Updated: 2023/09/08 20:31:42 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **final_split(char **args)
{
    int     i;

    i = -1;
    while (args && args[++i])
    {
        //expand variables
        //expand path
    }
    args = ft_subsplit(args, "<|>", -1);
    return (args);
}

void	check_args(char *out)
{
	char **args;
    t_cmdlist *cmd_list;

	if (!out)
	{
		printf("exit\n");
		return ;
	}
	if (out[0] != '\0')
		add_history(out);
	args = ft_split_cmds(out);
	printf("AFTER FT_SPLIT_CMDS:\n");
    ft_print_array(args);
	free(out);
    if (args)
        cmd_list = create_cmd_list(final_split(args), -1);
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
    ft_cmdlstclear(&cmd_list, free_cmd_content);

}

// // 2. create tokens

// // prompt loop function
// int	main(int argc, char *argv[], char *envp[])
// {
// 	// 1. get username
// 	// 2. get home directory
// 	// 3. display prompt string and wait for input
// 	char	*prompt;
// 	char	*out;
// 	// char	**array;
// 	// int		wordcount;
// 	// char	space = ' ';
// 	(void)argc;
// 	(void)argv;

// 	out = NULL;
// 	prompt = "jdaly@minishell$ ";
// 	while (1)
// 	{
// 		out = readline(prompt);
// 		check_args(out);

// 		// wordcount = ft_count_words(out);
// 		// printf("wordcount = %d\\n", wordcount);
// 		// array = ft_create_array(out, wordcount);
// 		// print_array(array);
// 	}
// }