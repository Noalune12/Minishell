#include "minishell.h"

// static bool	handle_operator(t_list **tokens, const char *str, 
// 	size_t *i, size_t *start)
// {
// 	t_redirect_error	error;
// 	size_t				op_len;

// 	if (*i > *start && !add_token_to_list(tokens,
// 		create_token(str, *start, *i - *start)))
// 		return (false);
// 	op_len = get_operator_len(str, *i);
// 	error = check_operator_syntax(str + *i);
// 	if (error != REDIR_SUCCESS)
// 	{
// 		handle_redirect_error(*tokens, error, str + *i);
// 		return (false);
// 	}
// 	if (!add_token_to_list(tokens, create_token(str, *i, op_len)))
// 		return (false);
// 	*i += op_len;
// 	*start = *i;
// 	return (true);
// }

// static void	handle_quotes(char c, bool *in_quotes, char *quote_type)
// {
// 	if (!*in_quotes)
// 	{
// 		*in_quotes = true;
// 		*quote_type = c;
// 	}
// 	else if (c == *quote_type)
// 	{
// 		*in_quotes = false;
// 		*quote_type = 0;
// 	}
// }

// static void	init_split_vars(bool *in_quotes, char *quote_type)
// {
// 	*in_quotes = false;
// 	*quote_type = 0;
// }

t_token *split_operators(t_token *tokens)
{
    t_token *result;
    t_token *current;
    t_token *next;
    char    *content;
    size_t  i;
    size_t  start;
    bool    in_quotes;
    char    quote_type;

    result = NULL;
    current = tokens;

    while (current)
    {
        content = current->content;
        i = 0;
        start = 0;
        in_quotes = false;
        quote_type = 0;

        while (content[i])
        {
            // Handle quotes
            if (is_quote(content[i]))
            {
                if (!in_quotes)
                {
                    in_quotes = true;
                    quote_type = content[i];
                }
                else if (content[i] == quote_type)
                {
                    in_quotes = false;
                    quote_type = 0;
                }
                i++;
                continue;
            }

            // If we find an operator outside quotes
            if (!in_quotes && is_operator(content[i], false))
            {
                // Add the text before the operator if any
                if (i > start)
                {
                    if (!add_token(&result, ft_strndup(content + start, i - start), NODE_COMMAND))
                    {
                        free_token_list(result);
                        return (NULL);
                    }
                }

                // Get operator length (handle || && >> <<)
                size_t op_len = get_operator_len(content, i);

                // Determine operator type
                t_node_type op_type;
                if (ft_strncmp(content + i, "|", op_len) == 0 && op_len == 1)
                    op_type = NODE_PIPE;
                else if (ft_strncmp(content + i, "||", op_len) == 0)
                    op_type = NODE_OR;
                else if (ft_strncmp(content + i, "&&", op_len) == 0)
                    op_type = NODE_AND;
                else if (ft_strncmp(content + i, ">", op_len) == 0 && op_len == 1)
                    op_type = NODE_REDIR_OUT;
                else if (ft_strncmp(content + i, "<", op_len) == 0 && op_len == 1)
                    op_type = NODE_REDIR_IN;
                else if (ft_strncmp(content + i, ">>", op_len) == 0)
                    op_type = NODE_APPEND;
                else if (ft_strncmp(content + i, "<<", op_len) == 0)
                    op_type = NODE_HEREDOC;
                else
                    op_type = NODE_COMMAND; // Default

                // Add the operator token
                if (!add_token(&result, ft_strndup(content + i, op_len), op_type))
                {
                    free_token_list(result);
                    return (NULL);
                }

                i += op_len;
                start = i;
                continue;
            }

            i++;
        }
        // Add any remaining content
        if (i > start)
        {
            if (!add_token(&result, ft_strndup(content + start, i - start), NODE_COMMAND))
            {
                free_token_list(result);
                return (NULL);
            }
        }

        next = current->next;
        free(current->content);
        free(current);
        current = next;
    }

    return (result);
}

// t_list	*split_operators(const char *str, size_t i, size_t start)
// {
// 	t_list	*tokens;
// 	bool	in_quotes;
// 	char	quote_type;

// 	tokens = NULL;
// 	init_split_vars(&in_quotes, &quote_type);
// 	while (str[i])
// 	{
// 		if (is_quote(str[i]))
// 		{
// 			handle_quotes(str[i], &in_quotes, &quote_type);
// 			i++;
// 		}
// 		else if (is_operator(str[i], in_quotes))
// 		{
// 			if (!handle_operator(&tokens, str, &i, &start))
// 				return (NULL);
// 		}
// 		else
// 			i++;
// 	}
// 	if (i > start && !add_token_to_list(&tokens,
// 		create_token(str, start, i - start)))
// 		return (NULL);
// 	return (tokens);
// }
