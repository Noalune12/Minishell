/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:36 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:21:37 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parsing.h"
#include "utils.h"

static bool	handle_first_part(t_token **result, const char *content,
							size_t *i, size_t *start)
{
	char	*str;

	if (*i <= *start)
		return (true);
	str = ft_strndup(content + *start, *i - *start);
	if (str == false)
		return (false);
	if (add_token(result, str, NODE_COMMAND) == false)
	{
		free(str);
		return (false);
	}
	free(str);
	return (true);
}

static bool	process_op(t_token **result, const char *content,
							size_t *i, size_t *start)
{
	size_t		op_len;
	t_node_type	op_type;
	char		*str;

	if (handle_first_part(result, content, i, start) == false)
		return (false);
	op_len = get_operator_len(content, *i);
	op_type = get_operator_type(content, *i, op_len);
	str = ft_strndup(content + *i, op_len);
	if (str == NULL)
		return (false);
	if (add_token(result, str, op_type) == false)
	{
		free(str);
		return (false);
	}
	*i += op_len;
	*start = *i;
	free(str);
	return (true);
}

static bool	add_final_token(t_token **result, const char *content,
													size_t start, size_t end)
{
	char	*str;

	str = ft_strndup(content + start, end - start);
	if (str == NULL)
		return (false);
	if (add_token(result, str, NODE_COMMAND) == false)
	{
		free(str);
		return (false);
	}
	free(str);
	return (true);
}

static bool	process_token_content(t_token **result, const char *content)
{
	t_tokenizer	data;

	ft_memset(&data, 0, sizeof(t_tokenizer));
	while (content[data.i])
	{
		if (is_quote(content[data.i]))
			handle_quotes(content[data.i++], &data.in_quotes, &data.quote_type);
		else if (!data.in_quotes && is_operator(content[data.i], false))
		{
			if (process_op(result, content, &data.i, &data.start) == false)
				return (false);
		}
		else
			data.i++;
	}
	if (data.i <= data.start)
		return (true);
	return (add_final_token(result, content, data.start, data.i));
}

void	split_operators(t_minishell *minishell)
{
	t_token	*result;
	t_token	*current;
	t_token	*next;

	if (minishell->exec_status == false)
		return ;
	result = NULL;
	current = minishell->token;
	while (current != NULL)
	{
		if (process_token_content(&result, current->content) == false)
		{
			free_token_list(result);
			minishell->exec_status = false;
			minishell->exit_status = 1;
			return ;
		}
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	minishell->token = result;
}
