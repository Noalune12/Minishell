#include "minishell.h"

t_list	*find_last_heredoc(t_list *start, t_list **last_heredoc)
{
	t_list	*current;
	t_list	*next;

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

int	is_last_heredoc(t_list *current, t_list *last_heredoc)
{
	return (last_heredoc && current == last_heredoc->next);
}

/**
 * @brief CA MARCHE PAAAASSSS POUR LE DERNIER FICHIER TEMP
 *
 * 
 */
void	handle_regular_heredoc(t_list *current)
{
	char	*tmp_filename;

	tmp_filename = handle_heredoc(current->content);
	if (tmp_filename)
		unlink(tmp_filename);
	free(tmp_filename);
}

int	handle_last_heredoc(t_list *current, int *error)
{
	char	*filename;

	filename = handle_heredoc(current->content);
	if (!filename)
	{
		*error = -1;
		return (0);
	}
	free(current->content);
	current->content = filename;
	return (1);
}
