#include "expand.h"
#include "libft.h"
#include "minishell.h"

static int	process_dollar_var(t_heredoc_data *data)
{
	if (!handle_heredoc_dollar_sign(data))
		return (0);
	return (1);
}

static int	process_exit_code(t_heredoc_data *data, int exit_code)
{
	if (!handle_exit_code(data->expanded, &data->i, &data->j, exit_code))
		return (0);
	return (1);
}

static int	process_heredoc_chars(t_heredoc_data *data, t_minishell *minishell)
{
	while (data->str && data->str[data->i])
	{
		if (data->str[data->i] == '$' && data->str[data->i + 1] \
				&& (data->str[data->i + 1] != '?' \
				&& ft_isalnum(data->str[data->i + 1])))
		{
			if (!process_dollar_var(data))
				return (0);
		}
		else if (data->str[data->i] == '$' && data->str[data->i + 1] == '?')
		{
			if (!process_exit_code(data, minishell->exit_status))
				return (0);
		}
		else
			data->expanded[(data->j)++] = data->str[(data->i)];
		data->i++;
	}
	return (1);
}

char	*expand_heredoc(char *str, t_minishell *minishell)
{
	t_heredoc_data	data;
	char			*save;
	int				ret;

	save = NULL;
	ret = init_heredoc_expand(&data, str, minishell);
	if (ret == 1)
	{
		save = ft_strdup("\0");
		if (save == NULL)
			return (NULL);
		return (save);
	}
	else if (ret == 2)
		return (NULL);
	if (!process_heredoc_chars(&data, minishell))
	{
		free(data.expanded);
		return (NULL);
	}
	if (data.expanded != NULL)
		data.expanded[data.j] = '\0';
	return (data.expanded);
}
