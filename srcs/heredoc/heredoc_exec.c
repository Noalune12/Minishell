/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:35 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:22:36 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "heredoc.h"
#include "libft.h"
#include "minishell.h"

t_token	*find_last_heredoc(t_token *start, t_token **last_heredoc)
{
	t_token	*current;
	t_token	*next;

	current = start;
	*last_heredoc = NULL;
	while (current)
	{
		next = current->next;
		if (ft_strcmp(current->content, "<<") == 0 && next)
		{
			*last_heredoc = current;
		}
		else if (is_op(current->content))
			return (current);
		current = next;
	}
	return (NULL);
}
