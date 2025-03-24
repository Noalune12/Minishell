#include "minishell.h"
#include "wildcard.h"
#include "heredoc.h"
#include "ast.h"
#include "exec.h"

static void	build_and_execute(t_minishell *minishell)
{
	build_ast(minishell);
	print_ast(minishell, minishell->ast_node, 0);
	if (g_signal_received != 0)
		minishell->exit_status = g_signal_received + 128;
	else if (minishell->ast_node)
		minishell->exit_status = exec_minishell(minishell->ast_node, minishell);
}

static void	process_command(t_minishell *minishell)
{
	tokenize_input(minishell);
	split_operators(minishell);
	check_heredoc(minishell);
	expand_wildcards(minishell);
	syntax_check(minishell);
	print_tokens(minishell);
	build_and_execute(minishell);
}

static int	process_input(t_minishell *minishell)
{
	minishell->input = read_input(minishell);
	if (g_signal_received != 0)
	{
		minishell->exit_status = g_signal_received + 128;
		return (0);
	}
	if (minishell->input == NULL)
	{
		// ft_dprintf(STDERR_FILENO, "exit\n");
		return (-1);
	}
	init_global();
	return (1);
}

void	minishell_main_loop(t_minishell *minishell)
{
	int	input_status;

	while (1)
	{
		handle_signal_main();
		free_token_list(minishell->token);
		minishell->token = NULL;
		input_status = process_input(minishell);
		if (input_status == -1)
			break ;
		if (input_status == 0)
			continue ;
		process_command(minishell);
		cleanup_loop(minishell);
	}
}
