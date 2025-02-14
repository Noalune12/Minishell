#include "minishell.h"

void	clear_token_list(t_list *token)
{
	t_list	*current;
	t_list	*next;

	if (!token)
		return ;
	current = token->next;
	token->next = NULL; // Réinitialise le pointeur next du premier nœud
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}

int	check_unclosed_quotes(char *input)
{
	size_t	i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
			{
				dprintf(STDERR_FILENO, CHAR_SYNTAX, quote); // a changer
				return (0);
			}
		}
		i++;
	}
	return (1);
}
