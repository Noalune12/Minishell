#include "minishell.h"

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
					return ;
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
