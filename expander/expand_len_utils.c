#include "expand.h"

size_t	get_result_len(char *str)
{
	size_t	i;
	size_t	len;
	bool	in_dquotes;

	i = 0;
	len = 0;
	in_dquotes = false;
	while (str && str[i])
	{
		if (str[i] == '"')
			in_dquotes = !in_dquotes;
		else if (str[i] == '\'' && !in_dquotes)
			;
		else
			len++;
		i++;
	}
	return (len);
}

static void	add_var_value_len(char *var_name, size_t *total_len)
{
	char	*var_value;

	var_value = getenv(var_name); // changer pour notre t_list env ?
	if (var_value)
		*total_len += ft_strlen(var_value);
}

size_t	get_expanded_str_len(char *str)
{
	size_t	i;
	size_t	total_len;
	char	*var_name;
	size_t	var_len;
	bool	in_squotes;
	bool	in_dquotes;

	i = 0;
	total_len = 0;
	in_squotes = false;
	in_dquotes = false;
	while (str && str[i])
	{
		if (!handle_quotes(str[i], &in_squotes, &in_dquotes))
			total_len++;
		else if (str[i] == '$' && str[i + 1])
		{
			i++;
			var_len = get_var_len(str, i);
			var_name = ft_substr(str, i, var_len);
			if (!var_name)
				return (0);
			add_var_value_len(var_name, &total_len);
			free(var_name);
			i += var_len - 1;
		}
		else
			total_len++;
		i++;
	}
	return (total_len);
}
