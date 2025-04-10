/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:40 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 12:41:53 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "env.h"
#include "libft.h"

int	find_env_var_node(char *var, t_list **env)
{
	char	*env_var;
	t_list	*temp;

	temp = *env;
	env_var = NULL;
	while (temp != NULL)
	{
		env_var = ft_strndup(temp->content, ft_strnlen(temp->content, '='));
		if (env_var == NULL)
		{
			free(var);
			return (1);
		}
		if (ft_strcmp(var, env_var) == 0)
		{
			free(env_var);
			break ;
		}
		free(env_var);
		temp = temp->next;
	}
	*env = temp;
	free(var);
	return (0);
}

static int	add_or_replace_condition(char *content, t_list **env,
	int add, t_list *temp)
{
	char	*temp_content;

	temp_content = NULL;
	if (temp && add)
	{
		temp_content = temp->content;
		temp->content = ft_strdup(content);
		if (temp->content == NULL)
		{
			temp->content = temp_content;
			return (1);
		}
		free(temp_content);
	}
	else if (temp == NULL)
	{
		if (add_node(env, content) == NULL)
			return (1);
	}
	return (0);
}

int	add_or_replace_env(char *content, t_list **env, int len, int add)
{
	t_list	*temp;
	char	*var;

	var = ft_strndup(content, len);
	temp = *env;
	if (var == NULL)
		return (1);
	if (find_env_var_node(var, &temp) == 1)
		return (1);
	if (add_or_replace_condition(content, env, add, temp) == 1)
		return (1);
	return (0);
}

int	add_export_to_env(char *cmds, t_list **env)
{
	int	i;

	i = 0;
	while (cmds[i] && cmds[i] != '=' && cmds[i] != '+')
		i++;
	if (cmds[i] == '=')
	{
		if (add_or_replace_env(cmds, env, i, 1) == 1)
			return (1);
	}
	else if (!cmds[i])
	{
		if (add_or_replace_env(cmds, env, i, 0) == 1)
			return (1);
	}
	else if (cmds[i] == '+' && cmds[i + 1] == '=')
	{
		if (add_or_append_env(cmds, env, i + 2) == 1)
			return (1);
	}
	return (0);
}
