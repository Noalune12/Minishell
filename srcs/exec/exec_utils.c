#include "minishell.h"
#include "env.h"
#include "ast.h"

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < s1_len)
		res[i++] = s1[j++];
	j = 0;
	while (j < s2_len)
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}


int	error_handling_exec(t_minishell *minishell, char *message)
{
	if (minishell)
	{
		free_list(minishell->envp);
		free_ast(minishell->ast_node);
		free_token_list(minishell->token);
		if (minishell->options)
			free(minishell->options);
		if (minishell->fd_in)
			close(minishell->fd_in);
		if (minishell->fd_out)
			close(minishell->fd_out);
		close_and_free_fds(&minishell->fds.fd_in);
		close_and_free_fds(&minishell->fds.fd_out);
	}
	if (message)
		ft_dprintf(STDERR_FILENO, "%s\n", message);
	return (1);
}

int	is_builtin(char *cmds)
{
	if (ft_strcmp(cmds, "echo\0") == 0
		|| ft_strcmp(cmds, "cd\0") == 0
		|| ft_strcmp(cmds, "pwd\0") == 0
		|| ft_strcmp(cmds, "export\0") == 0
		|| ft_strcmp(cmds, "unset\0") == 0
		|| ft_strcmp(cmds, "env\0") == 0
		|| ft_strcmp(cmds, "exit\0") == 0
		|| ft_strcmp(cmds, "options\0") == 0
		|| ft_strcmp(cmds, "ptree\0") == 0
		|| ft_strcmp(cmds, "ptokens\0") == 0)
		return (1);
	return (0);
}

void	free_tab(char **tab, int i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

int	start_as_file(t_ast *node)
{
	if (ft_strncmp(node->cmd->cmds[0], "./", 2) == 0
		|| ft_strncmp(node->cmd->cmds[0], "/", 1) == 0)
		return (1);
	return (0);
}
