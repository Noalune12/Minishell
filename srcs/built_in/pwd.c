#include "minishell.h"

int	ft_pwd(char **cmds)
{
	char	*cwd;

	if (cmds[1])
	{
		printf("bash: pwd: %s: invalid option\npwd: usage: pwd\n", cmds[1]);
		return (1);
	}
	cwd = getcwd(NULL, 0); //automatic allocation of memory needed to copy path /!\ if path is NULL because folder was deleted how to handle the difference
	if (cwd)
		printf("%s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (1);
	}
	free(cwd);
	return (0);
}
