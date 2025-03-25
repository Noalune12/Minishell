#include "built_in.h"
#include "ft_dprintf.h"
#include "minishell.h"
#include "options.h"
#include "common.h"

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
		ft_dprintf(STDOUT_FILENO, PRINT_UNACTIVATED, PTOKENS, BOLD_RED, RESET);
	if (minishell->options->display_ast == true)
		ft_dprintf(STDOUT_FILENO, PRINT_ACTIVATED, PTREE, GREEN, RESET);
	else
		ft_dprintf(STDOUT_FILENO, PRINT_UNACTIVATED, PTREE, BOLD_RED, RESET);
}

void	print_option(t_options_enum option, t_minishell *minishell)
{
	static const t_option_handler	handlers[] = {
	[AST] = ast_wrapper,
	[TOKENS] = tokens_wrapper,
	[OPTIONS] = options_wrapper,
	};

	if (option >= AST && option <= OPTIONS)
		handlers[option](minishell);
}

int	print_options_wrapper(char **cmds, t_minishell *minishell)
{
	(void) cmds;
	print_option(OPTIONS, minishell);
	return (0);
}
