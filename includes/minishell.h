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
# define READ_END 0
# define WRITE_END 1
# define ERR_QUOTE 1
# define ERR_DIR 2
# define ERR_CMD 6
# define ERR_PERM 10
# define ERR_DUP 7
# define ERR_FORK 8
# define ERR_PIPE 9

extern char **environ;

typedef struct	s_list
{
	struct s_list	*next;
	char			*name;
	char			*content;
	int				is_env;
}	t_list;

typedef struct s_cmdlist
{
	struct s_cmdlist	*next;
	void				*content;
}	t_cmdlist;

typedef struct	s_cmd_node
{
	char	**cmd;
	char	*path;
	int		in;
	int		out;
}	t_cmd_node;

// typedef struct s_prompt
// {
// 	char	**envp;
// 	t_list	*cmds;
// 	pid_t	pid;
// }	t_prompt;

// Error
void	*ft_error(int error_type, char *error_str, int error_code);

// Strings
void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		nb_args(char **args);
void	ft_putchar_fd(char ch, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *a);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char 	**split_string(char *str, char *delimiter);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_atoi(const char *a);
static int	num_len(int n);
char	*ft_itoa(int n);


// Arrays
void	ft_free_arr(char **arr);
int		ft_array_len(char **array);
void	ft_print_array(char **array);
void	ft_array_free(char ***array);
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
char	*get_content_by_name(t_list *head, const char *name);

// Command List
t_cmd_node	*init_cmd_node(void);
t_cmdlist	*ft_cmdlstnew(void *content);
void		ft_cmdlstadd_back(t_cmdlist **lst, t_cmdlist *newnode);
t_cmdlist	*ft_cmdlstlast(t_cmdlist *lst);
void		free_cmd_content(void *content);
void		ft_cmdlstclear(t_cmdlist **lst, void (*del)(void*));

// lexer
static int	ft_count_words(char *str);
static char	**ft_create_array(char *str, int wordcount);
char		**ft_split_cmds(char *s);
char		**ft_subsplit(char **array, char *set, int i);

// expansion
char	*expand_home(char *str, t_list *envlist);
void	expand_all(char **args, t_list *envlist);

// Create command list
t_cmdlist	*create_cmd_list(char **args, int i);

// exec
void	handle_esc(char *str);
int		ft_test_pipes(t_cmdlist *cmd_list);
void	exec_cmd(t_cmdlist *cmd_list, t_list *env);
void	*check_to_fork(t_cmdlist *cmd_list, int fd[2], t_list *env);
void	exec_fork(t_cmdlist *cmd, int fd[2], t_list *env);
void	*child_process(t_cmdlist *cmd, int fd[2], t_list *env);
void	*child_builtin(t_cmdlist *cmd, int fd[2], t_list *env);

// get fd
t_cmd_node	*get_outfile(t_cmd_node *node, char **args, int *i);
t_cmd_node	*get_outfile_append(t_cmd_node *node, char **args, int *i);
t_cmd_node	*get_infile(t_cmd_node *node, char **args, int *i);
t_cmd_node	*get_infile_heredoc(t_cmd_node *node, char **args, int *i);

// builtin
t_list	*ft_env_parser(t_list *env);
void	ft_env(t_list *env);
void	ft_echo(char **args);
int		ft_pwd(void);
int 	set_var(t_list **env, char *name, char *content);
void	unset_var(t_list **env, char *name);
void	ft_cd(t_cmd_node *node, t_list *env);
int 	ft_is_builtin(char *str);
void 	ft_find_right_paths(t_cmdlist *cmd_list);
char	**get_key_value_pair(char *arg);


#endif