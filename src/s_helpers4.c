/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_helpers4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:45 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/12 18:43:03 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_atoi(const char *a)
{
	int	nb;
	int	is_neg;
	int	found;

	found = 1;
	nb = 0;
	is_neg = 1;
	while (*a == 32 || (*a >= 9 && *a <= 13))
		a++;
	if (*a == 45)
		is_neg = -1;
	if (*a == 43 || *a == 45)
		a++;
	while (*a && found)
	{
		if (*a >= '0' && *a <= '9')
			nb = nb * 10 + *a - '0';
		else
			found = 0;
		a++;
	}
	return (nb * is_neg);
}

int	num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*new;
	long	nbr;
	int		size;

	size = num_len(n);
	nbr = (long)n;
	new = (char *)malloc(sizeof(char) * size + 1);
	if (!new)
		return (0);
	new[size--] = '\0';
	if (nbr == 0)
		new[0] = '0';
	if (nbr < 0)
	{
		nbr *= -1;
		new[0] = '-';
	}
	while (nbr)
	{
		new[size--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (new);
}
