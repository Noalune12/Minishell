#include "minishell.h"
#include "ft_dprintf.h"

int	check_parentheses_tokens(t_token *current, t_token *next,
								t_minishell *minishell)
{
	if (current->type == NODE_CLOSE_PAR && next->type == NODE_COMMAND)
	{
		ft_dprintf(STDERR_FILENO, STR_SYNTAX, next->content);
		minishell->exit_status = 2;
		minishell->exec_status = false;
		return (-1);
	}
	if (current->type == NODE_COMMAND && next->type == NODE_OPEN_PAR)
	{
		ft_dprintf(STDERR_FILENO, STR_SYNTAX, next->content);
		minishell->exit_status = 2;
		minishell->exec_status = false;
		return (-1);
	}
	return (0);
}

int	check_unbalanced_parenthesis(t_token *token, int *paren_count,
									t_minishell *minishell)
{
	if (token->type == NODE_OPEN_PAR)
		(*paren_count)++;
	else if (token->type == NODE_CLOSE_PAR)
	{
		(*paren_count)--;
		if (*paren_count < 0)
		{
			ft_dprintf(STDERR_FILENO, STR_SYNTAX, token->content);
			minishell->exit_status = 2;
			minishell->exec_status = false;
			return (-1);
		}
	}
	return (0);
}
