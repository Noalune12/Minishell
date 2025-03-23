#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "types.h"
# include "common.h"

typedef struct s_tokenizer
{
	size_t	i;
	size_t	start;
	bool	in_quotes;
	char	quote_type;
	char	*str;
}	t_tokenizer;


void	handle_quotes(char c, bool *in_quotes, char *quote_type);

#endif
