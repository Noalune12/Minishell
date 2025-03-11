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
	if (!to_update)
	{
		ft_dprintf(STDERR_FILENO, "Error: NULL pointer\n");
		return ;
	}
	*to_update = !(*to_update);
}

void	print_toggled_options(t_minishell *minishell)
{
	if (minishell->options->display_tokens == true)
		ft_dprintf(STDOUT_FILENO, PRINT_ACTIVATED, PTOKENS, GREEN, RESET);
	else
		ft_dprintf(STDOUT_FILENO, PRINT_UNACTIVATED, PTOKENS, RED, RESET);
	if (minishell->options->display_ast == true)
		ft_dprintf(STDOUT_FILENO, PRINT_ACTIVATED, PTREE, GREEN, RESET);
	else
		ft_dprintf(STDOUT_FILENO, PRINT_UNACTIVATED, PTREE, RED, RESET);
}

void	man_options(void)
{
	printf(OPTIONS_MAN, WHITE_BOLD, RESET, WHITE_BOLD, RESET, WHITE_BOLD, \
	RESET, WHITE_BOLD, RESET, WHITE_BOLD, RESET, WHITE_BOLD, RESET, \
	WHITE_BOLD, RESET, WHITE_BOLD, RESET, WHITE_BOLD, RESET, \
	WHITE_BOLD, RESET, WHITE_BOLD, RESET);
}

void	print_option(t_options_enum option, t_minishell *minishell)
{
	static const t_option_handler	handlers[] = {
	[AST] = ast_wrapper,
	[TOKENS] = tokens_wrapper,
	[OPTIONS] = options_wrapper,
	[MAN] = man_wrapper,
	};

	if (option >= AST && option <= MAN)
		handlers[option](minishell);
}

void	check_entry(t_minishell *minishell)
{
	if (minishell->input != NULL && (ft_strcmp(minishell->input, \
		"options ptree") == 0 || ft_strcmp(minishell->input, "ptree") == 0))
		update_options(&minishell->options->display_ast);
	else if (minishell->input != NULL && (ft_strcmp(minishell->input, \
		"options ptokens") == 0 || ft_strcmp(minishell->input, "ptokens") == 0))
		update_options(&minishell->options->display_tokens);
	else if (minishell->input != NULL && \
								ft_strcmp(minishell->input, "options") == 0)
		print_option(OPTIONS, minishell);
	else if (minishell->input != NULL && \
								ft_strcmp(minishell->input, "man options") == 0)
		print_option(MAN, minishell);
}
