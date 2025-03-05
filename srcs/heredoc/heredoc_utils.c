#include "minishell.h"

// int	g_signal_received2; // CA DEGAAAAAAAAGE CA

// /**
//  * @brief comportement pas vraiment gerer je comprend pas trop comment faore
//  *
//  */
// static void	heredoc_signal_handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		close(0);
// 		g_signal_received = sig;
// 	}
// }

static int	write_heredoc_line(int fd, char *line)
{
	if (!line)
		return (0);
	ft_dprintf(fd, "%s\n", line);
	free(line);
	return (1);
}

static void	write_to_heredoc_main_loot(t_heredoc_utils *data, char *delimiter)
{
	while (1)
	{
		if (data->prompt)
			data->line = readline(data->prompt);
		if (!data->line)
		{
			print_redirect_error(REDIR_HEREDOC_EOF, delimiter);
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

int	write_to_heredoc(char *file_name, char *delimiter)
{
	t_heredoc_utils	data;

	data.fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.fd == -1)
		return (-1);
	data.original_stdin = dup(STDIN_FILENO);
	if (data.original_stdin == -1)
	{
		close(data.fd);
		return (-1);
	}
	signal(SIGINT, heredoc_signal_handler);
	data.prompt = ft_strjoin(delimiter, "> ");
	if (!data.prompt)
	{
		close(data.fd);
		close(data.original_stdin);
		return (-1);
	}
	data.line = NULL;
	write_to_heredoc_main_loot(&data, delimiter);
	signal(SIGINT, signal_handler);
	free(data.prompt);
	if (data.line)
		free(data.line);
	close(data.fd);
	if (dup2(data.original_stdin, STDIN_FILENO) == -1)
	{
		close(data.original_stdin);
		return (-1);
	}
	close(data.original_stdin);
	return (0);
}

int	is_valid_heredoc_delimiter(char *token)
{
	if (!token)
		return (0);
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "||") == 0 || \
		ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 || \
		ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0 || \
		ft_strcmp(token, "(") == 0 || ft_strcmp(token, ")") == 0 || \
		ft_strcmp(token, "&&") == 0)
		return (0);
	return (1);
}

int	is_op(char *token)
{
	if (!token)
		return (0);
	if (ft_strcmp(token, "<<") == 0)
		return (0);
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "||") == 0)
		return (1);
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0)
		return (1);
	if (ft_strcmp(token, "(") == 0 || ft_strcmp(token, ")") == 0)
		return (1);
	if (ft_strcmp(token, ">>") == 0)
		return (1);
	if (ft_strcmp(token, "&&") == 0)
		return (1);
	return (0);
}
