#include "minishell.h"
#include "options.h"

/**
 * Idees d'options:
 * ptree
 * tokens chained list
 * options
 *
 *
 *
 */

void	update_options(bool *to_update)
{
	*to_update = !(*to_update);
}

void	print_tokens(t_minishell *minishell)
{

}

void	print_options(t_minishell *minishell)
{

}

void	print_option(t_options_enum option, t_minishell *minishell)
{
	const t_options_enum	print_option[] = {\
		[AST] = &print_ast, \
		[TOKENS] = &print_tokens, \
		[OPTIONS] = &print_options, \
	};

	if (option >= AST && option <= OPTIONS)
		print_option[option](minishell);
}

void	check_entry(t_minishell *minishell)
{
	if (minishell->input != NULL && ft_strcmp(minishell->input, "ptree") == 0)
		update_options(minishell->options->display_ast);
	else if (minishell->input != NULL && ft_strcmp(minishell->input, "ptokens") == 0)
		update_options(minishell->options->display_tokens);
	else if (minishell->input != NULL && ft_strcmp(minishell->input, "options") == 0)
		print_option(OPTIONS, minishell);
}
