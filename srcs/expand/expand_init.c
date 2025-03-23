#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "expand.h"
#include "libft.h"
#include "minishell.h"

int	init_expand_data(t_expand_data *data, char *str, t_minishell *minishell)
{
	size_t	expanded_len;

	expanded_len = get_expanded_str_len(str, minishell);
	data->expanded = malloc(sizeof(char) * (expanded_len + ft_strlen(str) + 1)); //  a discuter
	if (!data->expanded)
		return (0);
	data->str = str;
	data->env = minishell->envp;
	data->minishell = minishell;
	data->i = 0;
	data->j = 0;
	data->in_squotes = false;
	data->in_dquotes = false;
	return (1);
}

int	init_heredoc_expand(t_heredoc_data *data, char *str, t_minishell *minishell)
{
	data->expanded_len = get_expanded_str_len(str, minishell);
	data->expanded = malloc(sizeof(char) * (data->expanded_len + ft_strlen(str) + 1)); // + ft_strlen(str) ??
	if (data->expanded == NULL)
		return (0);
	data->i = 0;
	data->j = 0;
	return (1);
}
bool	init_expand_len_data(t_exp_len *data, t_minishell *minishell)
{
	data->i = 0;
	data->total_len = 0;
	data->var_len = 0;
	data->in_dquotes = false;
	data->in_squotes = false;
	data->var_name = NULL;
	data->exit_code_str = ft_itoa(minishell->exit_status);
	if (data->exit_code_str == NULL)
		return (false);
	return (true);
}
