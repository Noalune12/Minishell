#include "options.h"
#include "minishell.h"

void	ast_wrapper(t_minishell *minishell)
{
	if (minishell->options->display_ast)
		print_ast(minishell->ast_node, 0, &minishell->exec_status);
}

void	options_wrapper(t_minishell *minishell)
{
	print_toggled_options(minishell);
}

void	tokens_wrapper(t_minishell *minishell)
{
	print_tokens(minishell);
}
