#include "heredoc.h"
#include "minishell.h"

static int	validate_heredoc_syntax(t_token *current, t_minishell *minishell)
{
	while (current)
	{
		if (ft_strcmp(current->content, HEREDOC) == 0)
		{
			if (current->next == NULL)
			{
				ft_dprintf(STDERR_FILENO, NEWLINE_SYNTAX);
				minishell->exit_status = 2;
				return (-1);
			}
			else if (is_valid_heredoc_delimiter(current->next->content) != 1)
			{
				ft_dprintf(STDERR_FILENO, STR_SYNTAX, current->next->content);
				minishell->exit_status = 2;
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

static void	process_heredocs(t_token *start, t_token *last_heredoc, int *error)
{
	t_token	*current;
	t_token	*next;

	current = start;
	while (current && !is_op(current->content))
	{
		next = current->next;
		if (ft_strcmp(current->content, HEREDOC) == 0 && next)
		{
			current = next;
			next = current->next;
			if (is_last_heredoc(current, last_heredoc))
			{
				if (!handle_last_heredoc(current, error))
					return ;
			}
			else
				handle_regular_heredoc(current);
		}
		current = next;
	}
}

static int	process_command_heredocs(t_token *current, int *error)
{
	t_token	*last_heredoc;
	t_token	*pipe_token;

	while (current)
	{
		pipe_token = find_last_heredoc(current, &last_heredoc);
		if (*error == -1)
			return (-1);
		if (last_heredoc)
		{
			process_heredocs(current, last_heredoc, error);
			if (*error == -1)
				return (-1);
		}
		if (!pipe_token)
			break ;
		current = pipe_token->next;
	}
	return (0);
}

void	check_heredoc(t_minishell *minishell)
{
	int	error;

	if (minishell->exec_status == false)
		return ;
	error = 0;
	if (validate_heredoc_syntax(minishell->token, minishell) != 0)
	{
		minishell->exec_status = false;
		return ;
	}
	if (process_command_heredocs(minishell->token, &error) != 0)
	{
		if (return_global() == SIGINT)
			minishell->exit_status = 130;
		else
			minishell->exit_status = 2;
		minishell->exec_status = false;
		return ;
	}
}
