/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:42:26 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/12 17:59:33 by dlariono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_atoi_exit(const char *str, long *num)
{
	int	sign;

	sign = 1;
	*num = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign *= -1;
	if ((*str == '-' || *str == '+'))
		str++;
	if (!ft_isdigit(*str))
		return (-1);
	while (ft_isdigit(*str))
	{
		*num = 10 * *num + (*str - '0');
		str++;
	}
	if (*str && !ft_isspace(*str))
		return (-1);
	*num *= sign;
	return (0);
}

int	ft_exit(t_cmdlist *cmd_list, t_list *env, int *is_exit)
{
	t_cmd_node	*node;
	long		status;
	int			error;

	node = cmd_list->content;
	*is_exit = !cmd_list->next; //	if last command, is_exit flag = 1;
	if (*is_exit)
		ft_putstr_fd("exit\n", 2);
	if (!node->cmd || !node->cmd[1])
		return (0);
	error = ft_atoi_exit(node->cmd[1], &status);
	if (error == -1)
	{
		ft_putstr_fd("minishell: exit ", 2);
		ft_putstr_fd(node->cmd[1], 2);
		ft_putstr_fd(": number required\n", 2);
		return (255);
	}
	else if (node->cmd[2])
	{
		*is_exit = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (status < 0)
		status = 256;
	else
		status %= 256;
	return (status);
}
