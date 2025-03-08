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
		add_node(env, actual_pwd); // protection
		free(actual_pwd);
	}
}

void	update_shlvl(t_list *env)
{
	t_list	*shlvl_node;
	char	*next_lvl;
	int		shlvl;

	shlvl_node = find_env_node(env, "SHLVL");
	if (!shlvl_node)
	{
		add_node(&env, "SHLVL=1");
		return ;
	}
	if (shlvl_node)
	{
		shlvl = ft_atoi(shlvl_node->content + 6);
		if (shlvl > 999 || shlvl <= 0) // handle export SHLVL="string" (atoi return value)
		{
			ft_dprintf(STDERR_FILENO, "SHLVL too high, reset to 1");
			shlvl = 1;
		}
		else
			shlvl++;
		next_lvl = ft_itoa(shlvl);
		if (next_lvl)
		{
			free(shlvl_node->content);
			shlvl_node->content = ft_strjoin("SHLVL=", next_lvl); // protection
			free(next_lvl);
		}
	}
}

// int	nested_shell(t_list *env_list) // check if we launched shells inside shells
// {
// 	t_list	*shlvl_node;
// 	int		shlvl;

// 	shlvl_node = find_env_node(env_list, "SHLVL");
// 	if (shlvl_node)
// 	{
// 		shlvl = ft_atoi(shlvl_node->content + 6);
// 		return (shlvl > 1); // more than one level indicates nested shell
// 	}
// 	return (0);
// }
