#include <stdlib.h>

#include "expand.h"
#include "libft.h"
#include "minishell.h"

int	handle_dollar_sign(char *str, char *expanded, size_t *i, size_t *j, t_list *env)
{
	char	*var_name;
	size_t	var_len;

	(*i)++;
	var_len = get_var_len(str, *i);
	var_name = ft_substr(str, *i, var_len);
	if (!var_name)
		return (0);
	copy_var_value(var_name, expanded, j, env);
	free(var_name);
	*i += var_len - 1;
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
