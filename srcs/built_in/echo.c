/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:36 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:20:37 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "built_in.h"
#include "ft_dprintf.h"
#include "minishell.h"

static inline int	is_no_nl(char *str)
{
	int	i;

	if (str == NULL || str[0] != '-')
		return (0);
	i = 1;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_print_echo(char **cmds, int index, int no_nl)
{
	int	i;

	i = 0;
	while (cmds[index])
	{
		while (cmds[index][i])
		{
			ft_dprintf(STDOUT_FILENO, "%c", cmds[index][i]);
			i++;
		}
		index++;
		if (cmds[index])
			ft_dprintf(STDOUT_FILENO, " ");
		i = 0;
	}
	if (no_nl == 0)
		printf("\n");
	return (0);
}

int	ft_echo(char **cmds, t_minishell *minishell)
{
	int	no_nl;
	int	i;

	(void)minishell;
	i = 1;
	no_nl = 0;
	if (cmds[i] == NULL)
	{
		ft_dprintf(STDOUT_FILENO, "\n");
		return (0);
	}
	while (cmds[i] && is_no_nl(cmds[i]))
	{
		no_nl = 1;
		i++;
	}
	if (!cmds[i])
		return (0);
	ft_print_echo(cmds, i, no_nl);
	return (0);
}
