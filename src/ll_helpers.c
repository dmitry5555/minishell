# include "minishell.h"

// Allocates (with malloc(3)) and returns a new node.
// The member variable ’content’ is initialized with
// the value of the parameter ’content’.  The variable
// ’next’ is initialized to NULL


void	ft_add_new_node(t_list **env, const char *str1, const char *str2)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->name = ft_strndup(str1, sizeof(str1));
	new->content = ft_strndup(str2, sizeof(str2));
	new->next = *env;
	*env = new;
}

t_list	*ft_lstnew(void const *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	if (new != 0)
		new->content = (void *)content;
		new->next = 0;
	return (new);
}

// Counts the number of nodes in a list.

int ft_lstsize(t_list *lst)
{
	int i;
	t_list *node;

	i = 0;
	node = lst;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

// Adds the node ’new’ at the end of the list.

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;
	if (!lst||!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
}

// Adds the node ’new’ at the beginning of the list.

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if(*lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
}
//  Deletes and frees the given node and every
//  successor of that node, using the function ’del’
//  and free(3).
//  Finally, the pointer to the list must be set to
//  NULL.
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*node;

	if (lst == 0 || del == 0)
		return ;
	temp = *lst;
	while (temp)
	{
		node = temp->next;
		del(temp->content);
		free(temp);
		temp = node;
	}
	*lst = 0;
}
// Takes as a parameter a node and frees the memory of
// the node’s content using the function ’del’ given
// as a parameter and free the node.  The memory of
// ’next’ must not be freed.

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == 0 || del == 0)
		return ;
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}
// Iterates the list ’lst’ and applies the function
// ’f’ on the content of each node.

void ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*node;
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		node = temp->next;
		f(temp->content);
		temp = node;
	}
}
// Returns the last node of the list.

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*node;

	node = lst;
	if(!node)
		return (0);
	while(node->next)
		node = node->next;
	return (node);
}
// Iterates the list ’lst’ and applies the function
// ’f’ on the content of each node.  Creates a new
// list resulting of the successive applications of
// the function ’f’.  The ’del’ function is used to
// delete the content of a node if needed.

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),void (*del)(void *))
{
	t_list	*temp;
	t_list	*new_list;

	if (!lst||!f||!del)
		return (0);
	new_list = 0;
	while (lst)
	{
		temp = ft_lstnew((*f)(lst->content));
		if (!temp)
		{
			ft_lstclear(&temp, del);
			return (0);
		}
		ft_lstadd_back(&new_list, temp);
		lst = lst->next;
	}
	return (new_list);
}
