#include "minishell.h"

void	update_shlvl(t_list *env)
{
	t_list	*shlvl_node;
	char	*next_lvl;
	int		shlvl;

	shlvl_node = find_env_node(env, "SHLVL");
	if (shlvl_node)
	{
		shlvl = ft_atoi(shlvl_node->content + 6);
		if (shlvl > 999 || shlvl <= 0)
		{
			dprintf(STDERR_FILENO, "SHLVL too high, reset to 1"); // a modifier avec le vrai message derreur
			shlvl = 1;
		}
		else
			shlvl++;
		next_lvl = ft_itoa(shlvl);
		if (next_lvl)
		{
			free(shlvl_node->content);
			shlvl_node->content = ft_strjoin("SHLVL=", next_lvl);
			free(next_lvl);
		}
	}
}

int	nested_shell(t_list *env_list) // check if we launched shells inside shells
{
	t_list *shlvl_node;
	int		shlvl;

	shlvl_node = find_env_node(env_list, "SHLVL");
	if (shlvl_node)
	{
		shlvl = ft_atoi(shlvl_node->content + 6);
		return (shlvl > 1); // more than one level indicates nested shell
	}
	return (0);
}
