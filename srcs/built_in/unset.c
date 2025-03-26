/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:56 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 12:53:16 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	free_node(t_list *node)
{
	if (node)
	{
		free(node->content);
		free(node);
	}
}

static int	compare_remove_node(t_list **head, char *content,
	t_list *current, t_list *prev)
{
	if (ft_strncmp(current->content, content, ft_strlen(content)) == 0)
	{
		if (prev == NULL)
			*head = current->next;
		else
			prev->next = current->next;
		free_node(current);
		free(content);
		return (0);
	}
	else
		return (1);
}

int	remove_node(t_list **head, char *var)
{
	t_list	*current;
	t_list	*prev;
	char	*content;

	if (var == NULL)
		return (1);
	current = *head;
	prev = NULL;
	content = ft_strjoin(var, "=");
	if (content == NULL)
		return (1);
	while (current)
	{
		if (compare_remove_node(head, content, current, prev) == 0)
			return (0);
		prev = current;
		current = current->next;
	}
	free(content);
	return (0);
}

int	ft_unset(char **cmds, t_minishell *minishell)
{
	size_t	i;
	char	*var;
	int		ret;

	i = 0;
	ret = 0;
	if (cmds[++i] == NULL)
		return (ret);
	while (cmds[i])
	{
		var = ft_strdup(cmds[i]);
		if (var == NULL)
			ret = 1;
		if (remove_node(&minishell->envp, var) == 1)
			ret = 1;
		free(var);
		i++;
	}
	return (ret);
}
