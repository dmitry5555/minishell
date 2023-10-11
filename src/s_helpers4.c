/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_helpers4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:45 by jdaly             #+#    #+#             */
/*   Updated: 2023/10/12 01:09:43 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_string(char *str, char *delimiter)
{
	int		wordcount;
	char	*copy;
	char	*token;
	char	**array;
	int		i;

	copy = strdup(str);
	token = strtok(copy, delimiter);
	wordcount = 0;
	i = 0;
	while (token != NULL)
	{
		wordcount++;
		token = strtok(NULL, delimiter);
	}
	array = malloc(sizeof(char *) * (wordcount + 1));
	if (array == NULL)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		free(copy);
		return (NULL);
	}
	token = strtok(str, delimiter);
	while (token != NULL)
	{
		array[i] = strdup(token);
		i++;
		token = strtok(NULL, delimiter);
	}
	array[i] = NULL;
	free(copy);
	return (array);
}

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

static int	num_len(int n)
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
