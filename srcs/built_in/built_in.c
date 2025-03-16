#include "minishell.h"

#include "options.h"

typedef int (* t_builtin)(char **cmds, t_minishell *minishell);

static int	print_env(char **cmds, t_minishell *minishell)
{
	t_list	*temp;

	(void)cmds;
	temp = minishell->envp;
	while (temp)
	{
		if (ft_strchr(temp->content, '='))
			printf("%s\n", temp->content);
		temp = temp->next;
	}
	return (0);
}

static int	ft_builtin(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	i;
	static t_builtin	builtin[] = {&ft_pwd, &ft_cd, &print_env, &ft_unset,
		&ft_export, &ft_echo, &ft_exit, &print_options_wrapper, &update_ptree_wrapper, &update_ptokens_wrapper};
	static char	*builtin_name[] = {"pwd", "cd", "env", "unset", "export", "echo", "exit", "options", "ptree", "ptokens"};

	ret = 0;
	i = 0;
	while (i < 10)
	{
		if (ft_strcmp(node->cmd->cmds[0], builtin_name[i]) == 0)
			break ;
		i++;
	}
	ret = builtin[i](node->cmd->cmds, minishell);
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
		// close(minishell->fd_in); //TODO protect
	}
	if (minishell->fd_out)
	{
		dup2(minishell->fd_out, STDOUT_FILENO); //TODO protect
		// close(minishell->fd_out); //TODO protect
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
