#include "options.h"
#include "minishell.h"

void	print_tokens(t_minishell *minishell)
{
	t_token	*print_tokens;

	if (!minishell->options->display_tokens)
		return ;
	else
	{
		print_tokens = minishell->token;
		while (print_tokens)
		{
			printf("%sToken: [%s], Type: %d%s\n", RED, \
				print_tokens->content, print_tokens->type, RESET);
			print_tokens = print_tokens->next;
		}
	}
}
