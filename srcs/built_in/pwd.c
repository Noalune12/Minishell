#include "minishell.h"

static int	error_handling(char *str, char *message)
{
	if (str)
		free(str);
	ft_dprintf(STDERR_FILENO, "%s", message);
	return (1);
}

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
		error_handling(NULL, "pwd: error retrieving current directory: getcwd: cannot access parent directories: ");
		perror("");
		return (1);
	}
	free(cwd);
	return (0);
}
