#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "expand.h"
#include "libft.h"
#include "minishell.h"

bool	init_expand_data(t_expand_data *data, char *str, t_minishell *minishell)
{
	ssize_t	expanded_len;
	ssize_t 	min_len;

	expanded_len = get_expanded_str_len(str, minishell);
	if (expanded_len == -1)
		return (false);
	min_len = ft_strlen(str);
	if (expanded_len < min_len)
		expanded_len = min_len;
	data->expanded = malloc(sizeof(char) * (expanded_len + 1));
	if (!data->expanded)
		return (false);
	data->str = str;
	data->env = minishell->envp;
	data->minishell = minishell;
	data->i = 0;
	data->j = 0;
	data->in_squotes = false;
	data->in_dquotes = false;
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
