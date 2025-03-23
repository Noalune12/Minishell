#include <stdlib.h>

#include "expand.h"
#include "libft.h"
#include "minishell.h"

static int	process_dollar_var(char *str, char *expanded, size_t *i, size_t *j,
							t_list *env)
{
	if (!handle_dollar_sign(str, expanded, i, j, env))
		return (0);
	return (1);
}

static int	process_exit_code(char *expanded, size_t *i, size_t *j,
							int exit_code)
{
	if (!handle_exit_code(expanded, i, j, exit_code))
		return (0);
	return (1);
}

static int	process_heredoc_chars(char *str, char *expanded, size_t *i,
								size_t *j, t_list *env, t_minishell *minishell)
{
	while (str && str[*i])
	{
		if (str[*i] == '$' && str[*i + 1] &&
			(str[*i + 1] != '?' && ft_isalnum(str[*i + 1])))
		{
			if (!process_dollar_var(str, expanded, i, j, env))
				return (0);
		}
		else if (str[*i] == '$' && str[*i + 1] == '?')
		{
			if (!process_exit_code(expanded, i, j, minishell->exit_status))
				return (0);
		}
		else
			expanded[(*j)++] = str[(*i)];
		(*i)++;
	}
	return (1);
}

char	*expand_heredoc(char *str, t_list *env, t_minishell *minishell)
{
	char	*expanded;
	size_t	expanded_len;
	size_t	i;
	size_t	j;

	expanded_len = get_expanded_str_len(str, minishell);
	expanded = malloc(sizeof(char) * (expanded_len + 1));
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	if (!process_heredoc_chars(str, expanded, &i, &j, env, minishell))
	{
		free(expanded);
		return (NULL);
	}
	expanded[j] = '\0';
	return (expanded);
}
