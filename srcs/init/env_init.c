#include "minishell.h"

static t_list	*ft_get_env(char **envp)
{
	t_list	*env;
	size_t	i;

	i = 0;
	env = NULL;
	if (!envp || !envp[i]) // condition correcte ?
	{
		env = malloc(sizeof(t_list));
		if (!env)
			return (NULL);
		env->content = NULL;
		env->next = NULL;
		return (env);
	}
	while (envp[i])
	{
		add_node(&env, envp[i]); // protection
		i++;
	}
	return (env);
}

static int	create_minimal_env(t_list **env)
{
	char	*shlvl;
	char	*underscore;

	shlvl = "SHLVL=1"; // ignoble
	underscore = "_=/usr/bin/env"; // ignoble++
	add_node(env, shlvl); // protection
	add_node(env, underscore); // protection
	return (1); // la fonction return jamais 0 cest un probleme -> probablement si add_node fail
}

t_list	*env_init(char **envp)
{
	t_list	*set_up_env;

	set_up_env = ft_get_env(envp);
	if (!set_up_env)
		return (NULL);
	if (!set_up_env->content)
	{
		update_pwd(&set_up_env);
		if (!create_minimal_env(&set_up_env))
		{
			free_list(set_up_env);
			return (NULL);
		}
		return (set_up_env);
	}
	else
		update_shlvl(set_up_env);
	return (set_up_env);
}
