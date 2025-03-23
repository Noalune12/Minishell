#include <stdlib.h>

#include "expand.h"
#include "libft.h"
#include "minishell.h"

static inline bool	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

inline size_t	get_var_len(char *str, size_t i)
{
	size_t	var_len;

	var_len = 0;
	while (str[i + var_len] && is_var_char(str[i + var_len]))
		var_len++;
	return (var_len);
}

static void	add_var_value_len(char *var_name, size_t *total_len, t_list *env)
{
	char	*var_value;

	var_value = ft_getenv(var_name, env);
	if (var_value)
		*total_len += ft_strlen(var_value);
}

ssize_t	get_expanded_str_len(char *s, t_minishell *minishell)
{
	t_exp_len	data;

	if (init_expand_len_data(&data, minishell) == false)
		return (0);
	while (s && s[data.i])
	{
		if (!update_quotes_expand(s[data.i], &data.in_squotes, &data.in_dquotes, NULL))
		data.total_len++;
		else if (s[data.i] == '$' && s[data.i + 1] && s[data.i + 1] == '?')
		{
			data.total_len += ft_strlen(data.exit_code_str);
			data.i++;
		}
		else if (s[data.i] == '$' && s[data.i + 1])
		{
			data.i++;
			data.var_len = get_var_len(s,data. i);
			data.var_name = ft_substr(s, data.i, data.var_len);
			if (!data.var_name)
				return (0);
			add_var_value_len(data.var_name, &data.total_len, minishell->envp);
			free(data.var_name);
			data.i += data.var_len - 1;
		}
		else
			data.total_len++;
		data.i++;
	}
	free(data.exit_code_str);
	return (data.total_len);
}
