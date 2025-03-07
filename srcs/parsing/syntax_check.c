#include "minishell.h"

	/*

	https://claude.ai/chat/5a4305a3-c0f9-447a-ad5d-5ee7a29966bd

	syntax to check :
	si dernier node est un <<, >, <, >>, |, (, &&, ||

	si consecutive operateurs :

	CHECK IS PARENTHESIS NOT CLOSED
	
	*/


bool	paired_parenthesis_check(t_list *tokens)
{
	t_list	*current;

	current = tokens;
	while (current)
	{
		if (ft_strcmp(current->content, ")") == 0)
			return (true);
		else
			current = current->next;
	}
	return (false);

}

int	syntax_check(t_minishell *minishell)
{
	t_list	*current;

	current = minishell->token;
	while (current)
	{
		if (s(current) == -1);
	}
	if (x == -1)
	{
		minishell->exit_status = 1;
		return (-1);
	}
}
