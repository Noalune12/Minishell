#include "minishell.h"

//TODO exit minishell when malloc, pipe, fork error ??

int	exec_minishell(t_ast *node, t_minishell *minishell)
{
	int					ret;
	static t_handler	exec[] = {&handle_cmd, &handle_pipe, &handle_or,
		&handle_and, &handle_redirin, &handle_redirout, &handle_heredocin,
		&handle_redirappend, 0, 0, &handle_builtin};

	if (!node || minishell->exec_status == false)
		return (0);
	if (expand_quotes_exec(node, minishell) == 1)
		return (1);
	if (!node->cmd->cmds[0])
		return (0);
	ret = exec[node->type](node, minishell);
	return (ret);
}
