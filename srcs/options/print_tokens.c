#include "options.h"
#include "minishell.h"

void	print_tokens(t_minishell *minishell)
{
	t_token		*current;
	int			i;
	static char	*type_short[] = {
		"CMD", "PIPE", "OR", "AND", "IN", "OUT",
		"HDOC", "APP", "(", ")", "BUILT"
	};

	if (minishell->options->display_tokens == false)
		return ;
	printf(BOLD_RED"Tokens:\n"RESET);
	current = minishell->token;
	i = 0;
	while (current)
	{
		printf(BOLD_RED"  %d. "RESET, current->type);
		printf("%s%-4s"" → ", CYAN, type_short[current->type]);
		printf("%s%s%s\n", WHITE_BOLD, current->content, RESET);
		current = current->next;
		i++;
	}
}

int	update_ptokens_wrapper(char **cmds, t_minishell *minishell)
{
	(void) cmds;
	update_options(&minishell->options->display_tokens);
	return (0);
}

int	update_ptree_wrapper(char **cmds, t_minishell *minishell)
{
	(void) cmds;
	update_options(&minishell->options->display_ast);
	return (0);
}
