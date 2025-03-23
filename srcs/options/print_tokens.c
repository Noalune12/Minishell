#include "options.h"
#include "minishell.h"

void	print_tokens(t_minishell *minishell)
{
	t_token	*print_tokens;

	if (minishell->options->display_tokens == false)
		return ;
	else
	{
		print_tokens = minishell->token;
		while (print_tokens)
		{
			printf("%sToken: [%s], Type: %d%s\n", BOLD_RED, \
				print_tokens->content, print_tokens->type, RESET);
			print_tokens = print_tokens->next;
		}
	}
}

int	update_ptokens_wrapper(char **cmds, t_minishell *minishell)
{
	(void) cmds;
	update_options(&minishell->options->display_tokens);
	return (0);
}

int	update_ptree_wrapper(char **cmds, t_minishell *minishell)
{
	(void) cmds;
	update_options(&minishell->options->display_ast);
	return (0);
}
