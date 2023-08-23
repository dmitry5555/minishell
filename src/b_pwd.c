# include "minishell.h"

// get cwd - curr.wrk.dir and print it
int ft_pwd(void)
{
	char	cwd[1000000];

	if (getcwd(cwd, 1000000))
	{
		ft_putendl_fd(cwd, 1);
		return(0); // return status
	}
	else
		return(0); // return status
}