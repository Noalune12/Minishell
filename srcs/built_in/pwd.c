/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:54 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:20:55 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "built_in.h"
#include "ft_dprintf.h"

int	ft_pwd(char **cmds, t_minishell *minishell)
{
	char	*cwd;

	(void)minishell;
	if (cmds[1])
	{
		ft_dprintf(STDERR_FILENO, PWD_ERROR, cmds[1]);
		return (1);
	}
	cwd = getcwd(NULL, 4096);
	if (cwd)
		ft_dprintf(STDOUT_FILENO, "%s\n", cwd);
	else
	{
		ft_dprintf(STDERR_FILENO, CWD_ERROR, PWD_BI);
		perror("");
		return (1);
	}
	free(cwd);
	return (0);
}
