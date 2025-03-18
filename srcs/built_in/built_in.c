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

	minishell->fd_in = dup(STDIN_FILENO);
	minishell->fd_out = dup(STDOUT_FILENO);
	dup_fd(&minishell->fds.fd_in, STDIN_FILENO);
	dup_fd(&minishell->fds.fd_out, STDOUT_FILENO);
	ret = ft_builtin(node, minishell);
	dup2(minishell->fd_in, STDIN_FILENO);
	dup2(minishell->fd_out, STDOUT_FILENO);
	close(minishell->fd_in);
	close(minishell->fd_out);
	exec_minishell(node->left, minishell);
	exec_minishell(node->right, minishell);
	return (ret);
}
