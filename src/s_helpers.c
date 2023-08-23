# include "minishell.h"

// check if strings are identical
// return 0 if ok or difference for last character

int ft_strcmp(const char *str1, const char *str2)
{
	unsigned int i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	i++;
	}
	return (0);
}

//  counts number of arguments X in arr[x][y]

int	nb_args(char **args)
{
	int	i;

	i = 0;
	while(args[i])
		i++;
	return (i);
}

// writes char to fd

void	ft_putchar_fd(char ch, int fd)
{
	write(fd,&ch,1);
}

// writes a string to the file descriptor(can use fd 1 as default output )

void	ft_putstr_fd(char *str, int fd)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while(str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return ;
}

// write string to fd + add newline

void ft_putendl_fd(char *str, int fd)
{
	ft_putstr_fd(str,fd);
	ft_putchar_fd('\n',1);
}

// searches for the first occurrence of the character C in the string
// pointed STR returns a pointer to the first
// occurrence of the character c in the string
// str, or NULL if the character is not found

char *ft_strchr(const char *str, int c)
{
	size_t  i;

	i = 0;
	while (i <= ft_strlen(str))
	{
		if (str[i] == (unsigned char)c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

// copies the string pointed to, by SRC to DEST

size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t  src_size;
	size_t  i;

	src_size = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_size);
}

// returns a part of a string - string, start, length

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	new = (char *)malloc(len + 1);
	if (!new)
		return (0);
	ft_strlcpy(new, s + start, len + 1);
	return (new);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(dst);
	if (i > dstsize || dstsize == 0)
		return (dstsize + ft_strlen(src));
	j = 0;
	while ((i + j + 1) < dstsize && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, len + 1);
	ft_strlcat(str, s2, len + 1);
	return (str);
}

char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
