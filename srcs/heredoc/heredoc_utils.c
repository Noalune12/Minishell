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

typedef struct s_heredoc // nom horrible a modifier
{
	char	*default_prompt;
	char	*line;
	char	*prompt;
	int		fd;
	int		original_stdin;
}	t_heredoc_utils;

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
		else
			data->line = readline(data->default_prompt);
		if (!data->line || (ft_strcmp(data->line, delimiter) == 0))
			break ;
		if (!write_heredoc_line(data->fd, data->line))
			break ;
	}
}

int	write_to_heredoc(char *file_name, char *delimiter)
{
	t_heredoc_utils	data;

	data.fd = open(file_name, O_WRONLY | O_TRUNC, 0644);
	if (data.fd == -1)
		return (-1);
	data.original_stdin = dup(STDIN_FILENO); // protect
	signal(SIGINT, heredoc_signal_handler);
	data.prompt = ft_strjoin(delimiter, "> "); // protect
	data.default_prompt = "> ";
	write_to_heredoc_main_loot(&data, delimiter);
	signal(SIGINT, signal_handler);
	free(data.prompt);
	free(data.line);
	close(data.fd);
	dup2(data.original_stdin, STDIN_FILENO); // protect
	close(data.original_stdin);
	return (0);
}

int	is_op(char *token) // temporary name
{
	if (!token)
		return (0);
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "||") == 0)
		return (1);
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0) // pas sur, avec et sans ca fait la meme chose mais je fais peut etre pas les bons tests
		return (1);
	if (ft_strcmp(token, "(") == 0 || ft_strcmp(token, ")") == 0)
		return (1);
	// if (ft_strcmp(token, ">>") == 0)
	// 	return (1);
	if (ft_strcmp(token, "&&") == 0)
		return (1);
	return (0);
}
