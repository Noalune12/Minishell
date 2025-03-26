/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:24 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 12:59:13 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*find_env_node(t_list *env, const char *var_searched)
{
	size_t	len;

	len = ft_strlen(var_searched);
	while (env)
	{
		if (ft_strncmp(env->content, var_searched, len) == 0 \
			&& env->content[len] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_list	*add_node(t_list **env, char *content)
{
	t_list	*temp;
	t_list	*new_node;

	temp = *env;
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = ft_strdup(content);
	if (new_node->content == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	if (*env == NULL)
	{
		*env = new_node;
		return (new_node);
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return (new_node);
}
