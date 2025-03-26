/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:16:56 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:17:04 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <stddef.h>

# include "types.h"

typedef enum e_redirect_error	t_redirect_error;
typedef struct s_list			t_list;
typedef struct s_token			t_token;

typedef struct s_tokenizer
{
	size_t	i;
	size_t	start;
	bool	in_quotes;
	char	quote_type;
	char	*str;
}	t_tokenizer;

void		clear_token_list(t_list *token);
void		copy_with_quotes(char *dest, char *src, size_t *len);
void		handle_quotes(char c, bool *in_quotes, char *quote_type);

size_t		get_word_length(char *input, size_t start);
size_t		get_operator_len(const char *str, size_t pos);

int			check_unclosed_quotes(char *input);
int			is_quote(char c);
int			check_unbalanced_parenthesis(t_token *token, int *paren_count, \
														t_minishell *minishell);
int			check_parentheses_tokens(t_token *current, t_token *next, \
														t_minishell *minishell);

bool		is_operator(char c, bool in_quotes);
bool		is_redirection(char c);

t_node_type	get_operator_type(const char *content, size_t i, size_t op_len);

#endif
