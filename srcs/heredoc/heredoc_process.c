#include "heredoc.h"

char	*ft_reallocate(char *str, char c, int len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * (len + 2));
	if (!ret)
	{
		if (len > 1)
			free(str);
		printf("Malloc failed");
		return (NULL);
	}
	while (len > 1 && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	if (len > 1)
		free(str);
	return (ret);
}

void	check_quotes(const char input, bool *in_s_quote, bool *in_d_quote)
{
	if (input == '\'' && !(*in_d_quote))
	{
		if (*in_s_quote)
			*in_s_quote = false; // out of single quotes
		else
			*in_s_quote = true; // enter single quotes
	}
	else if (input == '\"' && !(*in_s_quote))
	{
		if (*in_d_quote)
			*in_d_quote = false; // out of double quotes
		else
			*in_d_quote = true; // enter double quotes
	}
}

char	*handle_quotes_exec(char *input)
{
	char	*result;
	int		len;
	bool	in_s_quote;
	bool	in_d_quote;

	result = NULL;
	len = 0;
	in_s_quote = false;
	in_d_quote = false;
	if (ft_strcmp(input, "\"\"") == 0 || ft_strcmp(input, "''") == 0)
	{
		result = ft_calloc(1, sizeof(char)); // TODO protect
		return (result);
	}
	while ((*input))
	{
		if ((*input == '\'' && !in_d_quote) || (*input == '\"' && !in_s_quote))
			check_quotes(*input, &in_s_quote, &in_d_quote);
		// if we are not in quotes, or in double quotes, or in single quotes
		else if ((in_s_quote && !in_d_quote) || (in_d_quote && !in_s_quote)
			|| (!in_s_quote && !in_d_quote))
		{
			len++;
			result = ft_reallocate(result, *input, len);
			if (!result)
				return (NULL);
		}
		input++;
	}
	return (result);
}

char	*handle_heredoc(char *delimiter)
{
	char	*file_name;
	char	*processed_delimiter;

	processed_delimiter = handle_quotes_exec(delimiter);
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
