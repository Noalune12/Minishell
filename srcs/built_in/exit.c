/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:38 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 12:39:14 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "exec.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "limits.h"
#include "minishell.h"

static int	check_arg_exit(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			break ;
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i])
		return (0);
	return (1);
}

static void	skip_whitespace_sign(char *str, int *sign, int *i)
{
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

static int	exit_return(char *str)
{
	unsigned long long	nb;
	int					sign;
	int					i;

	sign = 1;
	i = 0;
	nb = 0;
	skip_whitespace_sign(str, &sign, &i);
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (sign == -1 && (sign * (((long long)nb * 10) + (str[i] - 48))
				== LLONG_MIN) && (str[i + 1] == '\0'
				|| ft_isdigit(str[i + 1]) == 0))
			return (0);
		if ((long long)nb > (LLONG_MAX - (str[i] - 48)) / 10)
		{
			ft_dprintf(STDOUT_FILENO, EXIT_ERROR, str);
			return (2);
		}
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	if (sign == 1)
		return (nb % 256);
	return (256 - nb % 256);
}

int	ft_exit(char **cmds, t_minishell *minishell)
{
	int	ret;

	ret = 0;
	if (minishell->pid != 0)
		ft_dprintf(STDOUT_FILENO, "%s\n", EXIT);
	if (cmds[1] == NULL)
		ret = 0;
	else if (check_arg_exit(cmds[1]) == 0)
	{
		ft_dprintf(STDOUT_FILENO, EXIT_ERROR, cmds[1]);
		ret = 2;
	}
	else if (cmds[2])
	{
		ft_dprintf(STDOUT_FILENO, TOO_MANY_ARGS, EXIT);
		return (1);
	}
	else
		ret = exit_return(cmds[1]);
	if (minishell->pid == 0)
		return (ret);
	error_handling_exec(minishell, NULL);
	exit(ret);
}
