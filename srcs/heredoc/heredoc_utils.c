#include "heredoc.h"

int	is_valid_heredoc_delimiter(char *token)
{
	if (!token)
		return (0);
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "||") == 0 || \
		ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 || \
		ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0 || \
		ft_strcmp(token, "(") == 0 || ft_strcmp(token, ")") == 0 || \
		ft_strcmp(token, "&&") == 0)
		return (0);
	return (1);
}

int	is_op(char *token)
{
	if (!token)
		return (0);
	if (ft_strcmp(token, "<<") == 0)
		return (0);
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "||") == 0)
		return (1);
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0)
		return (1);
	if (ft_strcmp(token, "(") == 0 || ft_strcmp(token, ")") == 0)
		return (1);
	if (ft_strcmp(token, ">>") == 0)
		return (1);
	if (ft_strcmp(token, "&&") == 0)
		return (1);
	return (0);
}

int	is_last_heredoc(t_token *current, t_token *last_heredoc)
{
	return (last_heredoc && current == last_heredoc->next);
}

bool	check_expand(char *delimiter)
{
	size_t	i;

	i = 0;
	while (delimiter[i])
	{
		if (is_quote(delimiter[i]))
			return (false);
		i++;
	}
	return (true);
}
