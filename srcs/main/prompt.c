#include "minishell.h"

static void	free_input_setup(char *tmp, char *exit_code, char *prompt)
{
	if (tmp != NULL)
		free(tmp);
	if (exit_code != NULL)
		free(exit_code);
	if (prompt != NULL)
		free(prompt);
}

static char	*setup_exit_code(int code)
{
	char	*exit_code;
	char	*temp;

	exit_code = ft_itoa(code);
	if (exit_code == NULL)
		return (NULL);
	temp = ft_strjoin_free(RED"[", exit_code);
	if (temp == NULL)
		return (NULL);
	exit_code = ft_strjoin(temp, "]> "RESET);
	if (exit_code == NULL)
	{
		free_input_setup(temp, NULL, NULL);
		return (NULL);
	}
	free(temp);
	return (exit_code);
}

char	*read_input(t_minishell *minishell)
{
	char	*input;
	char	*prompt;
	char	*exit_code;
	int		code;

	code = minishell->exit_status;
	exit_code = setup_exit_code(code);
	if (exit_code == NULL)
		return (NULL);
	if (code == 0)
		prompt = ft_strjoin_free(GREEN_ARROW CYAN" minishell "RESET, exit_code);
	else
		prompt = ft_strjoin_free(RED_ARROW CYAN" minishell "RESET, exit_code);
	if (prompt == NULL)
		return (NULL);
	input = readline(prompt);
	free(prompt);
	if (input && *input)
		add_history(input);
	return (input);
}
