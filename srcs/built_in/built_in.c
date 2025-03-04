#include "minishell.h"

static void	print_env(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strchr(temp->content, '='))
			printf("%s\n", temp->content);
		temp = temp->next;
	}
}

static int	ft_builtin(t_ast *node, t_minishell *minishell)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(node->cmd->cmds[0], "pwd\0") == 0)
		ret = ft_pwd(node->cmd->cmds);
	if (ft_strcmp(node->cmd->cmds[0], "cd\0") == 0)
		ret = ft_cd(node->cmd->cmds, minishell->envp);
	if (ft_strcmp(node->cmd->cmds[0], "env\0") == 0)
		print_env(minishell->envp);
	if (ft_strcmp(node->cmd->cmds[0], "unset\0") == 0)
		ret = ft_unset(node->cmd->cmds, minishell);
	if (ft_strcmp(node->cmd->cmds[0], "export\0") == 0)
		ret = ft_export(node->cmd->cmds, &minishell->envp);
	if (ft_strcmp(node->cmd->cmds[0], "echo\0") == 0)
		ret = ft_echo(node->cmd->cmds, minishell);
	if (ft_strcmp(node->cmd->cmds[0], "exit\0") == 0)
		ret = ft_exit(node->cmd->cmds, minishell);
	return (ret);
}

int	handle_builtin(t_ast *node, t_minishell *minishell)
{
	int	ret;

	ret = ft_builtin(node, minishell);
	exec_minishell(node->left, minishell);
	exec_minishell(node->right, minishell);
	return (ret);
}
