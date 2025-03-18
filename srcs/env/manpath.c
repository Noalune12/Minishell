#include "minishell.h"

void	add_manpath_to_env(t_list **env)
{
	char	*cwd;
	char	*own_manpath;
	char	*temp;
	char	*temp2;

	if (!env)
		return ;
	cwd = getcwd(NULL, 4096); // 4094 ? 4096 ? Il faudrat que tu me reexplique
	if (!cwd)
		return ;
	temp = ft_strjoin(MANPATH, ":");
	if (!temp)
		return ;
	temp2 = ft_strjoin_free(temp, cwd); // faire un strjoin qui join 3 ou 4 parametres ?
	if (!temp2)
	{
		free(temp);
		return ;
	}
	own_manpath = ft_strjoin(temp2, "/man");
	free(temp2);
	free(temp);
	if (!own_manpath)
		return ;
	add_or_replace_env(own_manpath, env, 7, 1);
	free(own_manpath);
}
