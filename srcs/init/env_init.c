#include "minishell.h"
#include "env.h"

static t_list	*error_handling(void)
{
	ft_dprintf(STDERR_FILENO, "Malloc failed\n");
	return (NULL);
}

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
			return (error_handling());
		env->content = NULL;
		env->next = NULL;
		return (env);
	}
	while (envp[i])
	{
		if (add_node(&env, envp[i]) == NULL)
		{
			free_list(env);
			return (NULL);
		}
		i++;
	}
	return (env);
}

static int	error_handling_minimal_env(char *str, char *str2, int msg)
{
	if (str)
		free(str);
	if (str2)
		free(str2);
	if (msg == 1)
		ft_dprintf(STDERR_FILENO, "Malloc failed\n");
	return (0);
}

static int	create_minimal_env(t_list **env)
{
	char	*shlvl;
	char	*underscore;

	shlvl = ft_strdup("SHLVL=1");
	if (!shlvl)
		return (error_handling_minimal_env(NULL, NULL, 1));
	underscore = ft_strdup("_=/usr/bin/env");
	if (!underscore)
		return (error_handling_minimal_env(shlvl, NULL, 1));
	// add_node(env, manpath);
	if (add_node(env, shlvl) == NULL)// protection
		return (error_handling_minimal_env(shlvl, underscore, 0));
	add_manpath_to_env(env);
	if (add_node(env, underscore) == NULL) // protection
		return (error_handling_minimal_env(shlvl, underscore, 0));
	free(shlvl);
	free(underscore);
	return (1);
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
		if (create_minimal_env(&set_up_env) == 0)
		{
			free_list(set_up_env);
			return (NULL);
		}
		return (set_up_env);
	}
	else
	{
		add_manpath_to_env(&set_up_env);
		update_shlvl(set_up_env);
	}
	return (set_up_env);
}
