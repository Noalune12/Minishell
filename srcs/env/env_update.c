#include "minishell.h"
#include <unistd.h>
#include "common.h"
#include "env.h"

void	add_manpath_to_env(t_list **env)
{
	char	*cwd;
	char	*own_manpath;
	char	*temp;

	if (!env)
		return ;
	cwd = getcwd(NULL, 4096);
	if (!cwd)
		return ;
	temp = ft_strjoin_free(MANPATH, cwd);
	if (!temp)
		return ;
	own_manpath = ft_strjoin(temp, "/man");
	free(temp);
	if (!own_manpath)
		return ;
	add_or_replace_env(own_manpath, env, 7, 1);
	free(own_manpath);
}

void	update_pwd(t_list **env)
{
	char	*cwd;
	char	*actual_pwd;

	if (!env || !*env)
		return ;
	cwd = getcwd(NULL, 4096);
	if (!cwd)
		return ;
	actual_pwd = ft_strjoin_free(RESEARCHPWD, cwd);
	if (!actual_pwd)
		return ;
	if ((*env)->content == NULL)
		(*env)->content = actual_pwd;
	else
	{
		if (add_node(env, actual_pwd) == NULL)
		{
			free_list(*env);
			free(env);
		}
		free(actual_pwd);
	}
}
 /* toujours le soucis de +2 au SHLVL de base */
void	update_shlvl(t_list *env)
{
	t_shlvl	u;

	ft_memset(&u, 0, sizeof(t_shlvl));
	u.shlvl_node = find_env_node(env, SHLVL);
	if (u.shlvl_node == NULL)
	{
		if (add_node(&env, INIT_SHLVL) == NULL)
			free_list(env);
	}
	else
	{
		u.shlvl = ft_atoi(u.shlvl_node->content + 6);
		if (u.shlvl < 0 || u.shlvl >= 999)
		{
			if (u.shlvl >= 999)
				ft_dprintf(STDERR_FILENO, SHLVL_TOO_HIGH, u.shlvl + 1);
			u.shlvl = 0;
		}
		u.shlvl++;
		u.next_lvl = ft_itoa(u.shlvl);
		free(u.shlvl_node->content);
		if (u.next_lvl == NULL)
			return ;
		u.shlvl_node->content = ft_strjoin_free(RESEARCHSHLVL, u.next_lvl);
	}
}
