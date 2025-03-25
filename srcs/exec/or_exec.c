#include "minishell.h"
#include "ast.h"
#include "exec.h"

int	handle_or(t_ast *node, t_minishell *minishell)
{
	int	ret;

	ret = exec_minishell(node->left, minishell);
	minishell->exit_status = ret;
	if (ret != 0 && g_signal_received != SIGINT)
	{
		g_signal_received = 0;
		ret = exec_minishell(node->right, minishell);
	}
	return (ret);
}
