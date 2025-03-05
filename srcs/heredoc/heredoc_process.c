#include "heredoc.h"

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

void	handle_regular_heredoc(t_token *current)
{
	char	*tmp_filename;

	tmp_filename = handle_heredoc(current->content);
	if (tmp_filename)
		unlink(tmp_filename);
	free(tmp_filename);
}

int	handle_last_heredoc(t_token *current, int *error)
{
	char	*filename;
	bool	should_expand;

	should_expand = check_expand(current->content);
	filename = handle_heredoc(current->content);
	if (!filename)
	{
		*error = -1;
		return (0);
	}
	current->to_expand = should_expand;
	free(current->content);
	current->content = filename;
	return (1);
}
