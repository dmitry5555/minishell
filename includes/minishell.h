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

extern char **environ;

typedef struct	s_list
{
	struct s_list	*next;
	char			*name;
	char			*content;
	int				is_env;
}	t_list;

typedef struct	s_cmd_node
{
	char	**cmd;
	char	*path;
	int		in;
	int		out;
}	t_cmd_node;

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
void	ft_free_array(char **array);

// Arrays
int		ft_array_len(char **array);
void	ft_print_array(char **array);
void	ft_array_free(char **array);
char	**ft_dup_array(char **array);
char	**ft_array_replace_in(char ***array, char **subarray, int n);
char	**ft_array_extend(char **in, char *newstr);

// Lists
//t_list	*ft_lstnew(void const *content);
void	ft_add_new_node_start(t_list **env, const char *str1, const char *str2, int is_env);
void	ft_add_new_node_end(t_list **env, const char *str1, const char *str2, int is_env);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
void	ft_free_list(t_list *list);
void	ft_cleanup(t_list **env);


// lexer
int		ft_count_words(char *str);
char	**ft_create_array(char *str, int wordcount);
void	print_array(char **array);

// exec
void	exec_cmd(char **args, int input_fd, int output_fd);
void	handle_esc(char *str);
void	exec_cmd(char **args, int input_fd, int output_fd);
void	ft_echo(char **args);
int		ft_pwd(void);

// builtin
char	**get_key_value_pair(char *arg);
t_list	*ft_env();
int 	set_var(t_list **env, char *name, char *content, int is_env);
void	unset_var(t_list **env, char *name);
void	ft_cd();

#endif