#include "minishell.h"

typedef int (* t_handler)(t_ast *node, t_minishell *minishell);

int	handle_and(t_ast *node, t_minishell *minishell)
{
	int	ret;

	ret = exec_minishell(node->left, minishell);
	if (ret == 0)
		ret = exec_minishell(node->right, minishell);
	return (ret);
}

int	handle_or(t_ast *node, t_minishell *minishell)
{
	int	ret;

	ret = exec_minishell(node->left, minishell);
	if (ret != 0)
		ret = exec_minishell(node->right, minishell);
	return (ret);
}

int	exec_minishell(t_ast *node, t_minishell *minishell)
{
	int	ret;
	static t_handler	exec[] = {&handle_or, &handle_and, &handle_cmd,
		&handle_pipe, &handle_redirout, &handle_redirin, &handle_redirappend,
		&handle_heredocin, &handle_builtin};

	if (!node)
		return (0);
	ret = exec[node->type](node, minishell);
	return (ret);
}
