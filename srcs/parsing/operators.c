#include "minishell.h"
#include "parsing.h"

static bool	handle_first_part(t_token **result, const char *content,
							size_t *i, size_t *start)
{
	char	*str;

	if (*i <= *start)
		return (true);
	str = ft_strndup(content + *start, *i - *start);
	if (!str)
		return (false);
	if (!add_token(result, str, NODE_COMMAND))
	{
		free(str);
		return (false);
	}
	free(str);
	return (true);
}

static bool	process_operator(t_token **result, const char *content,
							size_t *i, size_t *start)
{
	size_t		op_len;
	t_node_type	op_type;
	char		*str;

	if (!handle_first_part(result, content, i, start))
		return (false);
	op_len = get_operator_len(content, *i);
	op_type = get_operator_type(content, *i, op_len);
	str = ft_strndup(content + *i, op_len);
	if (!str)
		return (false);
	if (!add_token(result, str, op_type))
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
			if (!process_operator(result, content, &data.i, &data.start))
				return (false);
		}
		else
			data.i++;
	}
	if (data.i <= data.start)
		return (true);
	return (add_final_token(result, content, data.start, data.i));
}

t_token	*split_operators(t_token *tokens, bool *exec_status)
{
	t_token	*result;
	t_token	*current;
	t_token	*next;

	if (*exec_status == false)
		return (NULL);
	result = NULL;
	current = tokens;
	while (current)
	{
		if (!process_token_content(&result, current->content))
		{
			free_token_list(result);
			*exec_status = false;
			return (NULL);
		}
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	return (result);
}
