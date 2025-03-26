/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:19 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:22:20 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "env.h"
#include "libft.h"
#include "minishell.h"

static t_list	*ft_get_env(char **envp)
{
	t_list	*env;
	size_t	i;

	i = 0;
	env = NULL;
	if (envp == NULL || envp[i] == NULL)
	{
		env = malloc(sizeof(t_list));
		if (env == NULL)
			return (NULL);
		env->content = NULL;
		env->next = NULL;
		return (env);
	}
	while (envp[i] != NULL)
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

static int	error_handling_minimal_env(char *str, char *str2)
{
	if (str)
		free(str);
	if (str2)
		free(str2);
	return (0);
}

static int	create_minimal_env(t_list **env)
{
	char	*shlvl;
	char	*underscore;

	shlvl = ft_strdup(INIT_SHLVL);
	if (shlvl == NULL)
		return (error_handling_minimal_env(NULL, NULL));
	underscore = ft_strdup(ENV_DEFAULT);
	if (underscore == NULL)
		return (error_handling_minimal_env(shlvl, NULL));
	if (add_node(env, shlvl) == NULL)
		return (error_handling_minimal_env(shlvl, underscore));
	add_manpath_to_env(env);
	if (add_node(env, underscore) == NULL)
		return (error_handling_minimal_env(shlvl, underscore));
	free(shlvl);
	free(underscore);
	return (1);
}

t_list	*env_init(char **envp)
{
	t_list	*set_up_env;

	set_up_env = ft_get_env(envp);
	if (set_up_env == NULL)
		return (NULL);
	if (set_up_env->content == NULL)
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
	}
	update_shlvl(set_up_env);
	return (set_up_env);
}
