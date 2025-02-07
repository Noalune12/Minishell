#include "minishell.h"

t_list	*split_env(char **envp)
{
	t_list	*returned_env;
	char	**split;
	size_t	i;

	if (envp == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		split = ft_split(envp, '='); // define '=' ? (maybe need '+=' define aswell)
		if (!split)
			return (NULL); // lstclear env ?
	}
}

t_list	*env_init(char **envp)
{
	t_list	*set_up_env;

	set_up_env = split_env(envp);
	if (!set_up_env)
		return (NULL);
	// set up SHLVL (bonus ? not sure mandatory) ? pre set up cd built-in ?
	return (set_up_env);
}
