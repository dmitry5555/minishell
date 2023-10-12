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
# define ERR_PIPESYN 10

extern int g_status;

typedef struct s_list
{
	struct s_list	*next;
	char			*name;
	char			*content;
}	t_list;

typedef struct s_cmdlist
{
	struct s_cmdlist	*next;
	void				*content;
}	t_cmdlist;

typedef struct s_cmd_node
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
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strchars_i(const char *s, char *set);
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
char	**split_string(char *str, char *delimiter);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_atoi(const char *a);
static int	num_len(int n);
char	*ft_itoa(int n);


// Arrays
int		ft_a_len(char **array);
void	ft_print_array(char **array);
void	ft_array_free(char ***array);
char	**ft_dup_array(char **array);
char	**ft_array_extend(char **in, char *newstr);
char	**ft_array_replace_in(char ***a, char **sub, int n);

// Lists
//t_list	*ft_lstnew(void const *content);
void	ft_add_new_node_start(t_list **env, const char *str1, const char *str2);
void	ft_add_new_node_end(t_list **env, const char *str1, const char *str2);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
void	ft_free_list(t_list *list);
void	ft_cleanup(t_list **env);
char	*env_cont(t_list *head, const char *name);

// lexer
char	**ft_split_cmds(const char *s, char *set);
char	**ft_subsplit(char const *s, char *set);

// command list helpers
t_cmd_node		*init_cmd_node(void);
t_cmdlist		*fill_cmdlst_error(t_cmdlist *cmds, char **args, char **tmp);
t_cmdlist		*ft_cmdlstnew(void *content);
t_cmdlist		*ft_cmdlstlast(t_cmdlist *lst);

void			ft_cmdlstadd_back(t_cmdlist **lst, t_cmdlist *newnode);
void			free_cmd_content(void *content);
void			ft_cmdlstclear(t_cmdlist **lst, void (*del)(void*));
void			print_cmd_list(t_cmdlist *cmd_list);
int				ft_cmdlstsize(t_cmdlist *lst);

// Create command list
t_cmdlist		*create_cmd_list(char **args, int i);

// get fd
t_cmd_node		*get_outfile(t_cmd_node *node, char **args, int *i);
t_cmd_node		*get_outfile_append(t_cmd_node *node, char **args, int *i);
t_cmd_node		*get_infile(t_cmd_node *node, char **args, int *i);
t_cmd_node		*get_infile_heredoc(t_cmd_node *node, char **args, int *i);

// expansion
char	*expand_vars(char *str, int i, t_list *envlist);
int		is_user_home(char *str, t_list *envlist);
char	*expand_home(char *str, t_list *envlist);
char	**final_split(char **args, t_list *envlist);

// exec
void	handle_esc(char *str);
int		ft_test_pipes(t_cmdlist *cmd_list);
void	exec_cmd(t_cmdlist *cmd_list, t_list *env);
void	sig_hand(int sig);

// builtin
t_list	*ft_env_parser(char **environ);
int		ft_echo(char **args);
int		ft_pwd(void);
void	ft_cd(t_cmd_node *node, t_list *env);
int		ft_env_print(t_list *env, int is_export);
int		ft_export(t_cmd_node *cmd, t_list *env);
void	ft_unset(t_cmd_node *cmd, t_list *env);
void	change_shlvl(t_list *env, int inc);
int		ft_exit(t_cmdlist *cmd_list, t_list *env, int *is_exit);

// builtin helpers
void	unset_var(t_list **env, char *name);
int		set_var(t_list **env, char *name, char *content);
char	**get_key_value_pair(char *arg);
int		ft_is_builtin(char *str);
void	ft_find_right_paths(t_cmdlist *cmd_list);

#endif