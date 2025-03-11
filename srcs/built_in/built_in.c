#include "minishell.h"


//TODO handle builtin if infile or outfile don't do in a fork

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
	int	save_fdin;
	int	save_fdout;

	save_fdin = dup(STDIN_FILENO);
	save_fdout = dup(STDOUT_FILENO);
	if (minishell->fd_in)
	{
		dup2(minishell->fd_in, STDIN_FILENO);
		close(minishell->fd_in); //TODO protect
	}
	if (minishell->fd_out)
	{
		dup2(minishell->fd_out, STDOUT_FILENO); //TODO protect
		close(minishell->fd_out); //TODO protect
	}
	ret = ft_builtin(node, minishell);
	dup2(save_fdin, STDIN_FILENO);
	dup2(save_fdout, STDOUT_FILENO);
	close(save_fdin);
	close(save_fdout);
	exec_minishell(node->left, minishell);
	exec_minishell(node->right, minishell);
	return (ret);
}
