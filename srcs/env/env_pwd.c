#include "minishell.h"
#include <unistd.h>

void	update_pwd(t_list **env)
{
	char	*cwd;
	char	*actual_pwd;

	if (!env || !*env)
		return ;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	actual_pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!actual_pwd)
		return ;
	if ((*env)->content == NULL)
		(*env)->content = actual_pwd;
	else
	{
		add_node(env, actual_pwd);
		free(actual_pwd);
	}
}
