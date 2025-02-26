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

/**
 * @brief probable de faire une struct juste pour cette fonction...
 *
 *
 */
int	write_to_heredoc(char *file_name, char *delimiter)
{
	int		fd;
	char	*line;
	int		original_stdin;
	char	*prompt;
	char	*default_prompt;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	original_stdin = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_signal_handler);
	prompt = ft_strjoin(delimiter, "> ");
	default_prompt = "> ";
	while (1)
	{
		if (prompt)
			line = readline(prompt);
		else
			line = readline(default_prompt);
		if (!line || (ft_strcmp(line, delimiter) == 0))
			break ;
		if (!write_heredoc_line(fd, line))
			break ;
	}
	signal(SIGINT, signal_handler);
	free(prompt);
	free(line);
	close(fd);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	return (0);
}

int	is_op(char *token) // temporary name
{
	if (!token)
		return (0);
	if (ft_strcmp(token, "|") == 0)
		return (1);
	if (ft_strcmp(token, "&&") == 0)
		return (1);
	if (ft_strcmp(token, "||") == 0)
		return (1);
	if (ft_strcmp(token, "(") == 0)
		return (1);
	if (ft_strcmp(token, ")") == 0)
		return (1);
	return (0);
}
