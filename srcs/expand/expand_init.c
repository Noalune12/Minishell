#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "expand.h"
#include "libft.h"
#include "minishell.h"

bool	init_expand_data(t_expand_data *data, char *str, t_minishell *minishell)
{
	size_t	expanded_len;

	ft_memset(data, 0, sizeof(t_expand_data));
	expanded_len = get_expanded_str_len(str, minishell);
	data->expanded = malloc(sizeof(char) * (expanded_len + ft_strlen(str) + 1));
	if (data->expanded == NULL)
		return (false);
	data->str = str;
	data->env = minishell->envp;
	data->minishell = minishell;
	return (true);
}

bool	init_expand_len_data(t_exp_len *data, t_minishell *minishell)
{
	ft_memset(data, 0, sizeof(t_exp_len));
	data->exit_code_str = ft_itoa(minishell->exit_status);
	if (data->exit_code_str == NULL)
		return (false);
	return (true);
}

bool	init_heredoc_expand(t_heredoc_data *data, char *str, \
														t_minishell *minishell)
{
	size_t	len;

	len = ft_strlen(str);
	ft_memset(data, 0, sizeof(t_heredoc_data));
	data->expanded_len = get_expanded_str_len(str, minishell);
	data->expanded = malloc(sizeof(char) * (data->expanded_len + len + 1));
	if (data->expanded == NULL)
		return (false);
	data->str = str;
	data->env = minishell->envp;
	return (true);
}
