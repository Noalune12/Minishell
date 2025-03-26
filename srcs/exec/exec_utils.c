/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:39 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:21:40 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "built_in.h"
#include "env.h"
#include "fd.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	res = malloc(sizeof(char) * (s1_len + ft_strlen(s2) + 1));
	if (res == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (i < s1_len)
		res[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen(s2))
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
	if (ft_strcmp(cmds, ECHO) == 0
		|| ft_strcmp(cmds, CD) == 0
		|| ft_strcmp(cmds, PWD_BI) == 0
		|| ft_strcmp(cmds, EXPORT) == 0
		|| ft_strcmp(cmds, UNSET) == 0
		|| ft_strcmp(cmds, ENV) == 0
		|| ft_strcmp(cmds, EXIT) == 0
		|| ft_strcmp(cmds, OPTIONS_BI) == 0
		|| ft_strcmp(cmds, PTREE_BI) == 0
		|| ft_strcmp(cmds, PTOKENS_BI) == 0)
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
