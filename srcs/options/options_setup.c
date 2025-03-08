#include "minishell.h"


/**
 * Idees d'options:
 * ptree
 * tokens
 * options
 *
 *
 *
 */

void	update_options(bool *to_update)
{
	*to_update = !(*to_update);
}

void	check_options(t_minishell *minishell)
{
	if (minishell->input != NULL && ft_strcmp(minishell->input, "ptree") == 0)
		update_options(minishell->options.display_ast);
	else if (minishell->input != NULL && ft_strcmp(minishell->input, "tokens") == 0)
		update_options(minishell->options.display_tokens);
}
