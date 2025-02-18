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
	// if(strncmp(node->content, "pwd", 3) == 0)
	// 	ft_pwd();
	// if(strncmp(node->content, "cd", 2) == 0)
	// 	ft_cd(node->content, exec->env);
	if(strncmp(node->cmd->cmds[0], "env\0", ft_strlen(node->cmd->cmds[0])) == 0)
		print_env(minishell->envp);
}
