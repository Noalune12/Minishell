#include "minishell.h"

void	free_input_setup(char *tmp, char *exit_code, char *prompt)
{
	if (tmp != NULL)
		free(tmp);
	if (exit_code != NULL)
		free(exit_code);
	if (prompt != NULL)
		free(prompt);
}

char	*read_input(t_minishell *minishell)
{
	char	*input;
	char	*prompt;
	char	*tmp;
	char	*exit_code;
	int		code;

	code = minishell->exit_status;
	exit_code = ft_itoa(code);
	tmp = ft_strjoin(RED"[", exit_code);
	if (tmp == NULL)
		return (NULL);
	free(exit_code);
	exit_code = ft_strjoin(tmp, RED"]> "RESET);
	if (exit_code == NULL)
	{
		free_input_setup(tmp, exit_code, NULL);
		return (NULL);
	}
	free(tmp);
	if (code == 0)
		prompt = ft_strjoin_free(GREEN_ARROW CYAN" minishell "RESET, exit_code);
	else
		prompt = ft_strjoin_free(RED_ARROW CYAN" minishell "RESET, exit_code);
	if (prompt == NULL)
	{
		free (exit_code);
		return (NULL);
	}
	input = readline(prompt);
	free(prompt);
	if (input && *input)
		add_history(input);
	return (input);
}
