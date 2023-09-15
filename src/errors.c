/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:07:05 by jdaly             #+#    #+#             */
/*   Updated: 2023/09/15 20:16:10 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// # define ERR_QUOTE 1
// # define ERR_DIR 2
// # define ERR_CMD 6
// # define ERR_DUP 7
// # define ERR_FORK 8
// # define ERR_PIPE 9

void    *ft_error(int error_type, char *error_str, int error_code)
{
    //global_status = error_code;
    if (error_type == ERR_QUOTE)
        ft_putstr_fd("minishell: cannot find closing quote", 2);
    if (error_type == ERR_DIR)
        ft_putstr_fd("minishell: no such file or directory: ", 2);
    if (error_type == ERR_CMD)
        ft_putstr_fd("minishell: command not found: ", 2);
    if (error_type == ERR_FORK)
        ft_putstr_fd("minishell: fork error", 2);
     if (error_type == ERR_PIPE)
        ft_putstr_fd("minishell: pipe error", 2);
    // if (error_type == ERR_)
    ft_putendl_fd(error_str, 2);
    return (NULL);
}