/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:26 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:54:59 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "minishell.h"

static int	handle_variable_expansion(t_expand_data *data)
{
	if (data->str[data->i] == '$' && data->str[data->i + 1]
		&& (ft_isalnum(data->str[data->i + 1]) \
		|| data->str[data->i + 1] == '_'))
	{
		*(data->exp) = 1;
		if (!handle_dollar_sign(data))
			return (0);
	}
	else if (data->str[data->i] == '$' && data->str[data->i + 1] == '?')
	{
		*(data->exp) = 1;
		if (!handle_exit_code(data->expanded, &(data->i), &(data->j),
				data->minishell->exit_status))
			return (0);
	}
	else
		data->expanded[data->j++] = data->str[data->i];
	return (1);
}

int	process_character(t_expand_data *data)
{
	if (data->str[data->i] == '$' && data->str[data->i + 1] == '"' \
									&& !data->in_squotes && !data->in_dquotes)
		return (handle_dollar_quoted(data, '"'));
	else if (data->str[data->i] == '$' && data->str[data->i + 1] == '\'' \
									&& !data->in_squotes && !data->in_dquotes)
		return (handle_dollar_quoted(data, '\''));
	else if (!update_quotes_expand(data->str[data->i], &(data->in_squotes), \
											&(data->in_dquotes), data->quote))
	{
		data->expanded[data->j] = data->str[data->i];
		data->j++;
		return (1);
	}
	else
		return (handle_variable_expansion(data));
}
