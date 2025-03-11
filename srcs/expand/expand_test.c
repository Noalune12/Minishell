#include "minishell.h"

static bool	handle_quotes(char c, bool *open_squotes, bool *open_dquotes)
{
	if (c == '\'' && !*open_squotes && !*open_dquotes)
	{
		*open_squotes = true;
		return (false);
	}
	else if (c == '"' && !*open_squotes && *open_dquotes)
	{
		*open_dquotes = false;
		return (true);
	}
	else if (c == '"' && !*open_squotes)
	{
		*open_dquotes = true;
		return (true);
	}
	return (true);
}

bool	determine_expand(char *str, size_t pos)
{
	size_t	i;
	bool	open_squotes;
	bool	open_dquotes;
	bool	to_expand;

	i = 0;
	to_expand = true;
	open_dquotes = false;
	open_squotes = false;
	while (str && str[i] && i < pos)
	{
		to_expand = handle_quotes(str[i], &open_squotes, &open_dquotes);
		i++;
	}
	return (to_expand);
}

int	check_token_expand(t_list *token, t_list *env) // boolean ?
{
	// remove quotes from content -> var_to_search
	char	*expand_to_search;
	size_t	len_to_search;


	len_to_search = ft_strlen(token->content) - 2;
	expand_to_search = ft_substr(token->content, 1, len_to_search);
	while (env)
	{
		if (ft_strncmp(env->content, token->content, len_to_search))
			; // ?
	}
}

void	handle_expand_idk(t_minishell *minishell)
{
	t_list	*tmp_token;

	tmp_token = minishell->token;
	while (tmp_token)
	{
		if (check_token_expand(tmp_token, minishell->envp))
		{
			tmp_token->content = replace_token_value_by_expand(tmp_token); // ?
		}
		tmp_token = tmp_token->next;
	}
}
