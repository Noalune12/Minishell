#include "expand.h"

static int	handle_dollar_sign(char *str, char *expanded, size_t *i, size_t *j, t_list *env)
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

void   	handle_expand(char *str, size_t *i)
{
	char	*var_name;
	char	*var_value;
	size_t	var_len;

	*i += 1;
	var_len = 0;
	while (str[*i + var_len] && (ft_isalnum(str[*i + var_len]) || \
			str[*i + var_len] == '_'))
		var_len++;
	var_name = ft_substr(str, *i, var_len);
	if (!var_name)
		return ;
	var_value = getenv(var_name); // aller chercher dans notre liste chainee ?
	printf("var value = %s & var name = %s", var_value, var_name);
	free(var_name);
	*i += var_len - 1;
}

char	*expand_env_vars(char *str, t_list *env)
{
	size_t	i;
	size_t	j;
	char	*expanded;
	size_t	expanded_len;
	bool	in_squotes;
	bool	in_dquotes;

	expanded_len = get_expanded_str_len(str, env);
	expanded = malloc(sizeof(char) * (expanded_len + 1));
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	in_squotes = false;
	in_dquotes = false;
	while (str && str[i])
	{
		if (!handle_quotes_expand(str[i], &in_squotes, &in_dquotes))
			expanded[j++] = str[i];
		else if (str[i] == '$' && str[i + 1] && str[i + 1] != '?')
		{
			if (!handle_dollar_sign(str, expanded, &i, &j, env))
			{
				free(expanded);
				return (NULL);
			}
		}
		else
			expanded[j++] = str[i];
		i++;
	}
	expanded[j] = '\0';
	return (expanded);
}
