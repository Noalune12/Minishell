#include "minishell.h"

int	ft_pwd(char **cmds, t_minishell *minishell)
{
	char	*cwd;

	(void)minishell;
	if (cmds[1])
	{
		ft_dprintf(STDERR_FILENO, PWD_ERROR, cmds[1]);
		return (1);
	}
	cwd = getcwd(NULL, 4094);
	if (cwd)
		ft_dprintf(STDOUT_FILENO, "%s\n", cwd);
	else
	{
		ft_dprintf(STDERR_FILENO, "getcwd failed\n");
		return (1);
	}
	free(cwd);
	return (0);
}
