/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:07 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 13:27:31 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static t_token	*init_token_node(char *content, t_node_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->content = ft_strdup(content);
	if (token->content == NULL)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->to_expand = true;
	token->next = NULL;
	return (token);
}

bool	add_token(t_token **tokens, char *content, t_node_type type)
{
	t_token	*new;
	t_token	*last;

	new = init_token_node(content, type);
	if (new == NULL)
		return (false);
	if (!*tokens)
		*tokens = new;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (true);
}

bool	add_token_in_place(t_token **tokens, char *content, t_node_type type)
{
	t_token	*new;

	new = init_token_node(content, type);
	if (new == NULL)
		return (false);
	if (*tokens == NULL)
		*tokens = new;
	else
	{
		new->next = (*tokens)->next;
		(*tokens)->next = new;
	}
	return (true);
}
