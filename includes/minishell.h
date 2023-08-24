#ifndef MINISHELL
# define MINISHELL

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_BUFFER_SIZE 100

extern char **environ; // Declaration for environment variables

typedef struct	s_list
{
	struct s_list	*next;
	char			*name;
	char			*content;
}	t_list;

// Strings
void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp(const char *str1, const char *str2);
int		nb_args(char **args);
void	ft_putchar_fd(char ch, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *a);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

// Lists
t_list	*ft_lstnew(void const *content);
void	ft_add_new_node(t_list **env, const char *str1, const char *str2);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),void (*del)(void *));

// lexer
int		ft_count_words(char *str);
char	**ft_create_array(char *str, int wordcount);
void	print_array(char **array);

// exec
void	exec_cmd(char **args, int input_fd, int output_fd);
void	handle_esc(char *str);
void	exec_cmd(char **args, int input_fd, int output_fd);
void	ft_echo(char **args);
char	**get_key_value_pair(char *arg);
int		ft_pwd(void);

#endif