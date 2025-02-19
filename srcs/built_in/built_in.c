#include "minishell.h"

static void	print_env(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}

void	ft_builtin(t_ast *node, t_minishell *minishell)
{
	if(strncmp(node->cmd->cmds[0], "pwd", ft_strlen(node->cmd->cmds[0])) == 0)
		ft_pwd(node->cmd->cmds);
	if(strncmp(node->cmd->cmds[0], "cd", ft_strlen(node->cmd->cmds[0])) == 0)
		ft_cd(node->cmd->cmds, minishell->envp);
	if(strncmp(node->cmd->cmds[0], "env\0", ft_strlen(node->cmd->cmds[0])) == 0)
		print_env(minishell->envp);
	if(strncmp(node->cmd->cmds[0], "unset\0", ft_strlen(node->cmd->cmds[0])) == 0)
		ft_unset(node->cmd->cmds, &minishell->envp);
}
