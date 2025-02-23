#include "minishell.h"

typedef int (* t_handler)(t_ast *node, t_minishell *minishell);

int	exec_minishell(t_ast *node, t_minishell *minishell)
{
	int	ret;
	t_handler	tab[] = {0, 0, &handle_cmd, &handle_pipe, &handle_redirout, &handle_redirin, &handle_redirappend, 0, &handle_builtin};

	if (!node)
		return (0);
	ret = tab[node->type](node, minishell);
	// printf("ret = %d\n", ret);
	// // else if (node->type == NODE_AND)
	// // {
	// // 	if (pipe(minishell->pipe_fd) == -1)
	// // 	{
	// // 		printf("Pipe error");
	// // 		return (1);
	// // 	}
	// // 	exec_minishell(node->left, exec, minishell);
	// // 	exec_minishell(node->right, exec, minishell);
	// // }
	return (ret);
}
