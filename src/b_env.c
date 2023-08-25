# include "minishell.h"

int	ft_env()
{
	t_list	*curr_env;

	curr_env = parse_env();
	print_list_values(curr_env);
	return(0);
}

int		main()
{
	ft_env();
}