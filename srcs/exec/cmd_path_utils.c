/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:34 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:14:53 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

void	free_join_full_path(t_path_cmds *path_cmds,	char *str,
	char **env, t_minishell *minishell)
{
	if (str)
		free(str);
	free(path_cmds->path_env);
	ft_free_double(path_cmds->paths);
	free_tab(env, ft_lstsize(minishell->envp));
}

int	error_handling_cmd_path(t_path_cmds *path_cmds,	char *str,
	char **env, t_minishell *minishell)
{
	free_join_full_path(path_cmds, str, env, minishell);
	error_handling_exec(minishell, NULL);
	return (1);
}

int	free_error_cmd_path(t_minishell *minishell,
	char *message, char **env, char *cmds)
{
	ft_dprintf(STDERR_FILENO, message, cmds);
	free_tab(env, ft_lstsize(minishell->envp));
	error_handling_exec(minishell, NULL);
	return (127);
}
