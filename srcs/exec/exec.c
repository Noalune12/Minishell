#include "minishell.h"

//list to tab

typedef int (* t_handler)(t_ast *node, t_minishell *minishell);

int	update_exit_code(int exit_code, t_minishell *minishell, t_ast *node)
{
	static int result;

	if (node->last_branch == 1)
	{
		result = exit_code;
	}
	printf("result = %d\n", result);
	minishell->exit_status = result;
	printf("exit status = %d\n", minishell->exit_status);
	return (0);
}

int	exec_minishell(t_ast *node, t_minishell *minishell)
{
	int	ret;
	t_handler	tab[] = {0, 0, &handle_cmd, &handle_pipe, &handle_redirout, &handle_redirin, &handle_redirappend, 0, &handle_builtin};

	if (!node)
		return (0);
	ret = tab[node->type](node, minishell);
	printf("ret = %d\n", ret);
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

	// // int exit_code;
	// // waitpid(minishell->pid, &minishell->status, 0);
	// // if (node->last_branch == 1)
	// // 	minishell->exit_code = WEXITSTATUS(minishell->status);
	// // printf("Le code de sortie de %s est : %d\n", node->cmd->cmds[0], minishell->exit_code);
	// // if (node->last_branch == 1)
	// // 	return (update_exit_code(minishell->exit_code, minishell, node));
	// // else
	// // 	return (0);
	// if (node->last_branch == 1)
	// {
	// 	waitpid(minishell->pid, &minishell->status, 0);
	// 	minishell->exit_status = WEXITSTATUS(minishell->status);
	// 	// minishell->exit_code = minishell->exit_status;
	// 	// return update_exit_code(minishell->exit_code, minishell, node);
	// }
	// else
	// 	waitpid(minishell->pid, NULL, 0);
	// printf("Le code de sortie de %s est : %d\n", node->cmd->cmds[0], minishell->exit_status);
	return (ret);
}
