#include "ast.h"
#include "minishell.h"
#include "options.h"

void	ast_wrapper(t_minishell *minishell)
{
	print_ast(minishell, minishell->ast_node, 0);
}

void	options_wrapper(t_minishell *minishell)
{
	print_toggled_options(minishell);
}

void	tokens_wrapper(t_minishell *minishell)
{
	print_tokens(minishell);
}
