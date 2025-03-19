#include <stdlib.h>

#include "expand.h"
#include "libft.h"
#include "minishell.h"

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

// static int	handle_exit_code(char *expanded, size_t *i, size_t *j, int exit_code)
// {
// 	char	*exit_code_str;

// 	(*i) += 1;
// 	exit_code_str = ft_itoa(exit_code);
// 	if (!exit_code_str)
// 		return (0);
// 	ft_strcpy(&expanded[*j], exit_code_str);
// 	*j += ft_strlen(exit_code_str);
// 	free(exit_code_str);
// 	return (1);
// }

static int handle_exit_code(char *expanded, size_t *i, size_t *j, int exit_code)
{
	char	*exit_code_str;
	size_t	k;

	(*i) += 1;
	exit_code_str = ft_itoa(exit_code);
	if (!exit_code_str)
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

char *expand_env_vars(char *str, t_list *env, t_minishell *minishell, int *exp, int *quote)
{
	size_t	i;
	size_t	j;
	char	*expanded;
	size_t	expanded_len;
	bool	in_squotes;
	bool	in_dquotes;

	expanded_len = get_expanded_str_len(str, env, minishell);
	expanded = malloc(sizeof(char) * (expanded_len + 1));
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	in_squotes = false;
	in_dquotes = false;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] == '"' && !in_squotes && !in_dquotes)
		{
			i += 2;
			while (str[i] && str[i] != '"')
				expanded[j++] = str[i++];
			if (str[i] == '"')
				i++;
		}
		else if (str[i] == '$' && str[i + 1] == '\'' && !in_squotes && !in_dquotes)
		{
			i += 2;
			while (str[i] && str[i] != '\'')
				expanded[j++] = str[i++];
			if (str[i] == '\'')
				i++;
		}
		else if (!handle_quotes_expand(str[i], &in_squotes, &in_dquotes, quote))
			expanded[j++] = str[i++];
		else if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			*exp = 1;
			if (!handle_dollar_sign(str, expanded, &i, &j, env))
			{
				free(expanded);
				return (NULL);
			}
			i++;
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			*exp = 1;
			if (!handle_exit_code(expanded, &i, &j, minishell->exit_status))
			{
				free(expanded);
				return (NULL);
			}
			i++;
		}
		else
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

char	*expand_heredoc(char *str, t_list *env, t_minishell *minishell)
{
	size_t	i;
	size_t	j;
	char	*expanded;
	size_t	expanded_len;
	// bool	in_squotes;
	// bool	in_dquotes;

	expanded_len = get_expanded_str_len(str, env, minishell);
	expanded = malloc(sizeof(char) * (expanded_len + 1));
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	// in_squotes = false;
	// in_dquotes = false;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] && (str[i + 1] != '?' && ft_isalnum(str[i + 1])))
		{
			if (!handle_dollar_sign(str, expanded, &i, &j, env))
			{
				free(expanded);
				return (NULL);
			}
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			if (!handle_exit_code(expanded, &i, &j, minishell->exit_status))
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
