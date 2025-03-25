#include "heredoc.h"
#include "minishell.h"
#include "expand.h"
#include "libft.h"

t_token	*find_last_heredoc(t_token *start, t_token **last_heredoc)
{
	t_token	*current;
	t_token	*next;

	current = start;
	*last_heredoc = NULL;
	while (current)
	{
		next = current->next;
		if (ft_strcmp(current->content, "<<") == 0 && next)
		{
			*last_heredoc = current;
		}
		else if (is_op(current->content))
			return (current);
		current = next;
	}
	return (NULL);
}
