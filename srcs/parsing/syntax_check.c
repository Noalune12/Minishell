#include "minishell.h"

	/*

	https://claude.ai/chat/5a4305a3-c0f9-447a-ad5d-5ee7a29966bd

	syntax to check :
	si dernier node est un <<, >, <, >>, |, (, &&, ||

	si consecutive operateurs :

	CHECK IS PARENTHESIS NOT CLOSED

	*/

static int	check_first_token(t_token *token, t_minishell *minishell)
{
	if (token->type == NODE_PIPE || token->type == NODE_OR
		|| token->type == NODE_AND || token->type == NODE_CLOSE_PAR)
	{
		ft_dprintf(STDERR_FILENO, STR_SYNTAX, token->content);
		minishell->exit_status = 2;
		minishell->exec_status = false;
		return (-1);
	}
	return (0);
}

static int	check_last_token(t_token *token, t_minishell *minishell)
{
	if (token->type != NODE_COMMAND && token->type != NODE_CLOSE_PAR)
	{
		ft_dprintf(STDERR_FILENO, NEWLINE_SYNTAX);
		minishell->exit_status = 2;
		minishell->exec_status = false;
		return (-1);
	}
	return (0);
}

static int	check_consecutive_operators(t_token *current, t_token *next,
									t_minishell *minishell)
{
	if ((current->type == NODE_PIPE || current->type == NODE_OR \
		|| current->type == NODE_AND)
		&& (next->type == NODE_PIPE || next->type == NODE_OR \
		|| next->type == NODE_AND || next->type == NODE_CLOSE_PAR))
	{
		ft_dprintf(STDERR_FILENO, STR_SYNTAX, next->content);
		minishell->exit_status = 2;
		minishell->exec_status = false;
		return (-1);
	}
	if ((current->type == NODE_REDIR_IN || current->type == NODE_REDIR_OUT \
		|| current->type == NODE_APPEND || current->type == NODE_HEREDOC)
		&& next->type != NODE_COMMAND)
	{
		ft_dprintf(STDERR_FILENO, STR_SYNTAX, next->content);
		minishell->exit_status = 2;
		minishell->exec_status = false;
		return (-1);
	}
	return (0);
}

static int	check_token_sequence(t_token *current, int *paren_count,
							t_minishell *minishell)
{
	t_token	*next;

	while (current)
	{
		if (check_unbalanced_parenthesis(current, paren_count, minishell) == -1)
			return (-1);
		next = current->next;
		if (next)
		{
			if (check_consecutive_operators(current, next, minishell) == -1
				|| check_parentheses_tokens(current, next, minishell) == -1)
				return (-1);
		}
		else if (check_last_token(current, minishell) == -1)
			return (-1);
		current = next;
	}
	return (0);
}

int	syntax_check(t_minishell *minishell)
{
	t_token	*current;
	int		paren_count;

	current = minishell->token;
	if (!current || !minishell->exec_status)
		return (0);
	if (check_first_token(current, minishell) == -1)
		return (-1);
	paren_count = 0;
	if (check_token_sequence(current, &paren_count, minishell) == -1)
		return (-1);
	if (paren_count > 0)
	{
		ft_dprintf(STDERR_FILENO, NEWLINE_SYNTAX);
		minishell->exit_status = 2;
		minishell->exec_status = false;
		return (-1);
	}
	return (0);
}
