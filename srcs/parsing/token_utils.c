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

int	check_syntax_error(char *token)
{
	size_t	i;
	int		cmd_part;

	i = 0;
	cmd_part = 1;
	if ((token[0] == '\'' && token[1] == '\'')
		|| (token[0] == '\"' && token[1] == '\"'))
		return (1);
	while (token[i] && token[i] != ' ')
	{
		if (is_quote(token[i]))
		{
			if (cmd_part)
			{
				dprintf(STDERR_FILENO, QUOTES_SYNTAX, token); // a modifier
				return (0);
			}
		}
		else if (token[i] == ' ')
			cmd_part = 0;
		i++;
	}
	return (1);
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
				dprintf(STDERR_FILENO, QUOTES_SYNTAX, &quote); // a modifier -> marche pas pour "''""""' pareil pour '"'""'''"""'' < ft_putendl_fd fonctionne...
				return (0);
			}
		}
		i++;
	}
	return (1);
}
