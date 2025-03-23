#include <stdlib.h>

#include "expand.h"
#include "libft.h"
#include "minishell.h"

static void	copy_var_value_heredoc(char *var_name, t_heredoc_data *data)
{
	char	*var_value;

	var_value = ft_getenv(var_name, data->env);
	if (var_value)
	{
		while (*var_value)
		{
			data->expanded[data->j] = *var_value;
			data->j++;
			var_value++;
		}
	}
}

int	handle_heredoc_dollar_sign(t_heredoc_data *data)
{
	char	*var_name;
	size_t	var_len;

	data->i++;
	var_len = get_var_len(data->str, data->i);
	var_name = ft_substr(data->str, data->i, var_len);
	if (!var_name)
		return (0);
	copy_var_value_heredoc(var_name, data);
	free(var_name);
	data->i += var_len - 1;
	return (1);
}

int	handle_dollar_sign(t_expand_data *data)
{
	char	*var_name;
	size_t	var_len;

	data->i++;
	var_len = get_var_len(data->str, data->i);
	var_name = ft_substr(data->str, data->i, var_len);
	if (!var_name)
		return (0);
	copy_var_value(var_name, data);
	free(var_name);
	data->i += var_len - 1;
	return (1);
}

int	handle_exit_code(char *expanded, size_t *i, size_t *j, int exit_code)
{
	char	*exit_code_str;
	size_t	k;

	(*i) += 1;
	exit_code_str = ft_itoa(exit_code);
	if (exit_code_str == NULL)
		return (0);
	k = 0;
	while (exit_code_str[k])
	{
		expanded[*j] = exit_code_str[k];
		(*j)++;
		k++;
	}
	free(exit_code_str);
	return (1);
}

char	*expand_env_vars(char *s, t_minishell *minishell, int *exp, int *quote)
{
	t_expand_data	data;

	if (!init_expand_data(&data, s, minishell))
		return (NULL);
	data.exp = exp;
	data.quote = quote;
	while (s && s[data.i])
	{
		if (!process_character(&data))
		{
			free(data.expanded);
			return (NULL);
		}
		data.i++;
	}
	data.expanded[data.j] = '\0';
	return (data.expanded);
}
