#include "built_in.h"
#include "libft.h"
#include "minishell.h"
#include "options.h"
#include "ast.h"
#include "exec.h"

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

static int	dup_fd_builtin(t_minishell *minishell)
{
	if (dup_fd(&minishell->fds.fd_in, STDIN_FILENO) == 0)
	{
		close(minishell->fd_in);
		close(minishell->fd_out);
		return (error_handling_exec(NULL, "Dup2 failed"));
	}
	if (dup_fd(&minishell->fds.fd_out, STDOUT_FILENO) == 0)
	{
		close(minishell->fd_in);
		close(minishell->fd_out);
		return (error_handling_exec(NULL, "Dup2 failed"));
	}
	return (0);
}

int	handle_builtin(t_ast *node, t_minishell *minishell)
{
	int	ret;

	minishell->fd_in = dup(STDIN_FILENO);
	if (minishell->fd_in == -1)
		return (error_handling_exec(NULL, "Dup failed"));
	minishell->fd_out = dup(STDOUT_FILENO);
	if (minishell->fd_out == -1)
	{
		close(minishell->fd_in);
		return (error_handling_exec(NULL, "Dup failed"));
	}
	if (dup_fd_builtin(minishell) == 1)
		return (1);
	ret = ft_builtin(node, minishell);
	if (dup2(minishell->fd_in, STDIN_FILENO) == -1) // TODO recheck how to protect
		exit (error_handling_exec(minishell, "Dup2 failed"));
	if (dup2(minishell->fd_out, STDOUT_FILENO) == -1)
		exit (error_handling_exec(minishell, "Dup2 failed"));
	close(minishell->fd_in);
	close(minishell->fd_out);
	exec_minishell(node->left, minishell);
	exec_minishell(node->right, minishell);
	return (ret);
}
