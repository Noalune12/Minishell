/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:30 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 13:43:07 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>

#include "ft_dprintf.h"
#include "heredoc.h"
#include "libft.h"
#include "signals.h"

static int	write_heredoc_line(int fd, char *line)
{
	if (!line)
		return (0);
	ft_dprintf(fd, "%s\n", line);
	free(line);
	return (1);
}

static void	write_heredoc_loop(t_heredoc_utils *data, char *delimiter)
{
	while (1)
	{
		if (return_global() == SIGINT)
		{
			data->line = NULL;
			break ;
		}
		if (data->prompt)
			data->line = readline(data->prompt);
		if (data->line == NULL)
		{
			rl_replace_line("", 0);
			rl_done = 1;
			ft_dprintf(STDERR_FILENO, HEREDOC_ERROR_MESSAGE, delimiter);
			break ;
		}
		if (ft_strcmp(data->line, delimiter) == 0)
		{
			free(data->line);
			data->line = NULL;
			break ;
		}
		if (!write_heredoc_line(data->fd, data->line))
			break ;
	}
}

static int	init_heredoc_data(t_heredoc_utils *data, char *file_name,
							char *delimiter)
{
	data->fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd == -1)
		return (-1);
	data->original_stdin = dup(STDIN_FILENO);
	if (data->original_stdin == -1)
	{
		close(data->fd);
		return (-1);
	}
	data->prompt = ft_strjoin(delimiter, "> ");
	if (!data->prompt)
	{
		close(data->fd);
		close(data->original_stdin);
		return (-1);
	}
	data->line = NULL;
	return (0);
}

static int	cleanup_heredoc_data(t_heredoc_utils *data, int *original_stdin)
{
	free(data->prompt);
	close(data->fd);
	if (data->line)
		free(data->line);
	if (*original_stdin != -1)
	{
		if (dup2(*original_stdin, STDIN_FILENO) == -1)
		{
			close(*original_stdin);
			return (-1);
		}
		close(*original_stdin);
	}
	return (0);
}

int	write_to_heredoc(char *file_name, char *delimiter)
{
	t_heredoc_utils	data;
	int				original_stdin;
	int				result;
	int				previous_signal;

	if (init_heredoc_data(&data, file_name, delimiter) != 0)
		return (-1);
	original_stdin = data.original_stdin;
	previous_signal = return_global();
	write_heredoc_loop(&data, delimiter);
	result = cleanup_heredoc_data(&data, &original_stdin);
	if (previous_signal != 0)
	{
		g_signal_received = previous_signal;
	}
	return (result);
}
