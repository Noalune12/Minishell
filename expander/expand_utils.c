#include "expand.h"

static size_t	get_env_var_len(char *var_name)
{
	char	*var_value;
	size_t	len;

	len = 0;
	var_value = getenv(var_name); // changer pour notre propre t_list *env ?
	if (var_value)
		len = ft_strlen(var_value);
	return (len);
}

void	copy_var_value(char *var_name, char *expanded, size_t *j)
{
	char	*var_value;

	var_value = getenv(var_name); // changer pour notre propre t_list *env ?
	if (var_value)
	{
		while (*var_value)
		{
			expanded[*j] = *var_value;
			(*j)++;
			var_value++;
		}
	}
}

size_t	process_var_len(char *str, size_t *i)
{
	char	*var_name;
	size_t	var_len;
	size_t	len;

	(*i)++;
	var_len = get_var_len(str, *i);
	var_name = ft_substr(str, *i, var_len);
	if (!var_name)
		return (0);
	len = get_env_var_len(var_name);
	free(var_name);
	*i += var_len - 1;
	return (len);
}

void	add_var_value_len(char *var_name, size_t *total_len)
{
	char	*var_value;

	var_value = getenv(var_name); // changer pour notre t_list env ?
	if (var_value)
		*total_len += ft_strlen(var_value);
}
