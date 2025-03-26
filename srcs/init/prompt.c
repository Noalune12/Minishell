/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:14 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 14:03:39 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>

#include "common.h"
#include "exec.h"
#include "libft.h"
#include "minishell.h"

static char	*free_input_setup(char *tmp, char *exit_code)
{
	if (tmp != NULL)
		free(tmp);
	if (exit_code != NULL)
		free(exit_code);
	return (NULL);
}

static char	*setup_exit_code(int code)
{
	char	*exit_code;
	char	*temp;

	exit_code = ft_itoa(code);
	if (exit_code == NULL)
		return (NULL);
	temp = ft_strjoin_free(RED"[", exit_code);
	if (temp == NULL)
		return (free_input_setup(NULL, exit_code));
	exit_code = ft_strjoin_free_s1(temp, "]> "RESET);
	if (exit_code == NULL)
		return (free_input_setup(temp, exit_code));
	return (exit_code);
}

char	*read_input(t_minishell *minishell)
{
	char	*exit_code;
	char	*input;
	char	*prompt;
	int		code;

	code = minishell->exit_status;
	exit_code = setup_exit_code(code);
	if (exit_code == NULL)
		return (NULL);
	if (code == 0)
		prompt = ft_strjoin(GREEN_ARROW CYAN" minishell "RESET, exit_code);
	else
		prompt = ft_strjoin(RED_ARROW CYAN" minishell "RESET, exit_code);
	free(exit_code);
	if (prompt == NULL)
		input = readline(DEFAULT_PROMPT);
	else
		input = readline(prompt);
	if (prompt != NULL)
		free(prompt);
	if (input && *input)
		add_history(input);
	return (input);
}
