/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:21 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:49:38 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "minishell.h"

bool	init_expand_data(t_expand_data *data, char *str, t_minishell *minishell)
{
	size_t	expanded_len;

	ft_memset(data, 0, sizeof(t_expand_data));
	expanded_len = get_expanded_str_len(str, minishell);
	data->expanded = malloc(sizeof(char) * (expanded_len + 1));
	if (data->expanded == NULL)
		return (false);
	data->str = str;
	data->env = minishell->envp;
	data->minishell = minishell;
	return (true);
}

int	init_heredoc_expand(t_heredoc_data *data, char *str, \
														t_minishell *minishell)
{
	if (str == NULL)
		return (1);
	ft_memset(data, 0, sizeof(t_heredoc_data));
	data->expanded_len = get_expanded_str_len(str, minishell);
	data->expanded = malloc(sizeof(char) * (data->expanded_len + 1));
	if (data->expanded == NULL)
		return (2);
	data->str = str;
	data->env = minishell->envp;
	return (0);
}
