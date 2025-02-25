#include "minishell.h"

int	g_signal_received2; // CA DEGAAAAAAAAGE CA

static void	heredoc_signal_handler(int sig) // comportement pas vraiment gerer je comprend pas trop comment faore
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(0);
		g_signal_received2 = 130;
	}
}

static int	write_heredoc_line(int fd, char *line)
{
	if (!line)
		return (0);
	ft_dprintf(fd, "%s\n", line);
	free(line);
	return (1);
}

static int	write_to_heredoc(char *file_name, char *delimiter)
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

static char	*process_delimiter(char *delimiter)
{
	char	*processed;
	int		i;
	int		j;

	if (!delimiter)
		return (NULL);
	processed = malloc(sizeof(char) * (ft_strlen(delimiter) + 1));
	if (!processed)
		return (NULL);
	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if (!is_quote(delimiter[i]))
			processed[j++] = delimiter[i];
		i++;
	}
	processed[j] = '\0';
	return (processed);
}

char	*handle_heredoc(char *delimiter)
{
	char	*file_name;
	char	*processed_delimiter;

	// expand = check_expand(delimiter); -> si jamais on veut check les expands
	processed_delimiter = process_delimiter(delimiter);
	if (!processed_delimiter)
		return (NULL);
	file_name = create_temp_file();
	if (!file_name)
	{
		free(processed_delimiter);
		return (NULL);
	}
	if (write_to_heredoc(file_name, processed_delimiter) == -1)
	{
		free(processed_delimiter);
		free(file_name);
		return (NULL);
	}
	free(processed_delimiter);
	return (file_name);
}

static int	is_op(char *token)
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

t_list	*find_last_heredoc(t_list *start, t_list **last_heredoc)
{
	t_list	*current;
	t_list	*next;

	current = start;
	*last_heredoc = NULL;
	while (current)
	{
		next = current->next;
		if (ft_strcmp(current->content, "<<") == 0 && next)
		{
			*last_heredoc = current;
		}
		else if (is_op(current->content))
			return (current);
		current = next;
	}
	return (NULL);
}

static int	is_last_heredoc(t_list *current, t_list *last_heredoc)
{
	return (last_heredoc && current == last_heredoc->next);
}

static void	handle_regular_heredoc(t_list *current)
{
	char	*tmp_filename;

	tmp_filename = handle_heredoc(current->content);
	if (tmp_filename)
		unlink(tmp_filename); // marche PAAAASSSS
	free(tmp_filename);
}

static int	handle_last_heredoc(t_list *current, int *error)
{
	char	*filename;

	filename = handle_heredoc(current->content);
	if (!filename)
	{
		*error = -1;
		return (0);
	}
	free(current->content);
	current->content = filename;
	return (1);
}

static void	process_heredocs(t_list *start, t_list *last_heredoc, int *error)
{
	t_list	*current;
	t_list	*next;

	current = start;
	while (current && ft_strcmp(current->content, "|") != 0)
	{
		next = current->next;
		if (ft_strcmp(current->content, "<<") == 0 && next)
		{
			current = next;
			next = current->next;
			if (is_last_heredoc(current, last_heredoc))
			{
				if (!handle_last_heredoc(current, error))
					return;
			}
			else
				handle_regular_heredoc(current);
		}
		current = next;
	}
}

int	check_heredoc(t_minishell *minishell)
{
	t_list	*current;
	t_list	*last_heredoc;
	t_list	*pipe_token;
	int		error;

	current = minishell->token;
	error = 0;

	while (current)
	{
		pipe_token = find_last_heredoc(current, &last_heredoc);

		if (last_heredoc)
		{
			process_heredocs(current, last_heredoc, &error);
			if (error == -1)
				return (-1);
		}

		if (!pipe_token)
			break;
		current = pipe_token->next;
	}

	return (0);
}
