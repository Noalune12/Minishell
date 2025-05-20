/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_calc_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:17 by lbuisson          #+#    #+#             */
/*   Updated: 2025/05/20 14:28:08 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "minishell.h"

static size_t	handle_dollar_question(t_minishell *minishell, size_t *i)
{
	char	*exit_str;
	size_t	len;

	(*i)++;
	exit_str = ft_itoa(minishell->exit_status);
	if (!exit_str)
		return (1);
	len = ft_strlen(exit_str);
	free(exit_str);
	return (len);
}

static size_t	handle_dollar_var(char *s, t_minishell *minishell, size_t *i)
{
	size_t	var_len;
	char	*var_name;
	char	*var_value;
	size_t	len;

	(*i)++;
	var_len = 0;
	while (s[*i + var_len] && (ft_isalnum(s[*i + var_len])
			|| s[*i + var_len] == '_'))
		var_len++;
	var_name = ft_substr(s, *i, var_len);
	if (!var_name)
		return (0);
	var_value = ft_getenv(var_name, minishell->envp, 0);
	len = 0;
	if (var_value)
		len = ft_strlen(var_value);
	free(var_name);
	*i = *i + var_len - 1;
	return (len);
}

static size_t	process_dollar(char *s, t_minishell *minishell, size_t *i)
{
	if (s[*i + 1] == '$')
		return (1);
	else if (s[*i + 1] == '?')
		return (handle_dollar_question(minishell, i));
	else if (s[*i + 1] && (ft_isalnum(s[*i + 1]) || s[*i + 1] == '_'))
		return (handle_dollar_var(s, minishell, i));
	return (1);
}

int	handle_dollar_quoted(t_expand_data *data, char quote_char)
{
	(data->i) += 2;
	while (data->str[data->i] && data->str[data->i] != quote_char)
		data->expanded[data->j++] = data->str[data->i++];
	if (data->str[data->i] == quote_char)
		(data->i)++;
	(data->i)--;
	return (1);
}

ssize_t	get_expanded_str_len(char *s, t_minishell *minishell)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			len++;
		else if (s[i] == '$')
			len += process_dollar(s, minishell, &i);
		else
			len++;
		i++;
	}
	return (len + 1);
}
