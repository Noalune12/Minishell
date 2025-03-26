/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:26 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:22:27 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "libft.h"
#include "minishell.h"
#include "parsing.h"
#include "types.h"

int	is_valid_heredoc_delimiter(char *token)
{
	if (token == NULL)
		return (0);
	if (ft_strcmp(token, PIPE) == 0 || ft_strcmp(token, OR) == 0 || \
		ft_strcmp(token, REDIRIN) == 0 || ft_strcmp(token, REDIROUT) == 0 || \
		ft_strcmp(token, HEREDOC) == 0 || ft_strcmp(token, APPEND) == 0 || \
		ft_strcmp(token, OPEN_PAR) == 0 || ft_strcmp(token, CLOSE_PAR) == 0 || \
		ft_strcmp(token, AND) == 0)
		return (0);
	return (1);
}

int	is_op(char *token)
{
	if (token == NULL)
		return (0);
	if (ft_strcmp(token, HEREDOC) == 0)
		return (0);
	if (ft_strcmp(token, PIPE) == 0 || ft_strcmp(token, OR) == 0)
		return (1);
	if (ft_strcmp(token, OPEN_PAR) == 0 || ft_strcmp(token, CLOSE_PAR) == 0)
		return (1);
	if (ft_strcmp(token, AND) == 0)
		return (1);
	return (0);
}

int	is_last_heredoc(t_token *current, t_token *last_heredoc)
{
	return (last_heredoc && current == last_heredoc->next);
}

bool	check_expand(char *delimiter)
{
	size_t	i;

	i = 0;
	while (delimiter[i])
	{
		if (is_quote(delimiter[i]))
			return (false);
		i++;
	}
	return (true);
}
