/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:10 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:21:11 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	replace_token(t_list *current, t_list *new_tokens)
{
	t_list	*next;
	t_list	*new_next;
	char	*new_content;

	if (new_tokens == NULL)
		return (true);
	next = current->next;
	new_content = ft_strdup(new_tokens->content);
	if (new_content == NULL)
		return (false);
	free(current->content);
	current->content = new_content;
	current->next = new_tokens->next;
	free(new_tokens->content);
	free(new_tokens);
	if (current->next == NULL)
	{
		current->next = next;
		return (true);
	}
	new_next = ft_lstlast(current->next);
	new_next->next = next;
	return (true);
}
