#include <stdlib.h>

#include "expand.h"
#include "libft.h"
#include "minishell.h"

static void	add_var_value_len(char *var_name, size_t *total_len, t_list *env)
{
	char	*var_value;

	var_value = ft_getenv(var_name, env); // changer pour notre t_list env ?
	if (var_value)
		*total_len += ft_strlen(var_value);
}

size_t	get_expanded_str_len(char *str, t_list *env, t_minishell *minishell)
{
	size_t	i;
	size_t	total_len;
	char	*var_name;
	size_t	var_len;
	bool	in_squotes;
	bool	in_dquotes;
	char	*exit_code_str;

	i = 0;
	total_len = 0;
	in_squotes = false;
	in_dquotes = false;
	exit_code_str = ft_itoa(minishell->exit_status);
	if (!exit_code_str)
		return (0);
	while (str && str[i])
	{
		if (!handle_quotes_expand(str[i], &in_squotes, &in_dquotes))
			total_len++;
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			total_len += ft_strlen(exit_code_str);
			i++;
		}
		else if (str[i] == '$' && str[i + 1])
		{
			i++;
			var_len = get_var_len(str, i);
			var_name = ft_substr(str, i, var_len);
			if (!var_name)
				return (0);
			add_var_value_len(var_name, &total_len, env);
			free(var_name);
			i += var_len - 1;
		}
		else
			total_len++;
		i++;
	}
	free(exit_code_str);
	return (total_len);
}

static inline bool	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

size_t	get_var_len(char *str, size_t i)
{
	size_t	var_len;

	var_len = 0;
	while (str[i + var_len] && is_var_char(str[i + var_len]))
		var_len++;
	return (var_len);
}
