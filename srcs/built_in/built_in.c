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

static void	ft_echo(t_minishell *minishell)
{
	printf("%d\n", minishell->exit_status);
}

static int	ft_builtin(t_ast *node, t_minishell *minishell)
{
	int	ret = 0;

	if(strcmp(node->cmd->cmds[0], "pwd\0") == 0)
		ft_pwd(node->cmd->cmds);
	if(strcmp(node->cmd->cmds[0], "cd\0") == 0)
		ft_cd(node->cmd->cmds, minishell->envp);
	if(strcmp(node->cmd->cmds[0], "env\0") == 0)
		print_env(minishell->envp);
	if(strcmp(node->cmd->cmds[0], "unset\0") == 0)
		ft_unset(node->cmd->cmds, minishell);
	if(strncmp(node->cmd->cmds[0], "export\0", ft_strlen(node->cmd->cmds[0])) == 0)
		ret = ft_export(node->cmd->cmds, &minishell->envp);
	if(strncmp(node->cmd->cmds[0], "echp\0", ft_strlen(node->cmd->cmds[0])) == 0)
		ft_echo(minishell);
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
