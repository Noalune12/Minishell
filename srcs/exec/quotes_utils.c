/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:03 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:35:49 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "heredoc.h"
#include "libft.h"

static char	*ft_reallocate(char *str, char c, int len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * (len + 2));
	if (ret == NULL)
	{
		if (len > 0)
			free(str);
		return (NULL);
	}
	while (len > 1 && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	if (len > 0)
		free(str);
	return (ret);
}

static void	init_data(t_quotes *data, char *input)
{
	data->in_dquotes = false;
	data->in_squotes = false;
	data->original = input;
	data->len = 0;
	data->result = ft_calloc(1, sizeof(char));
}

static int	handle_quotes_main_loop(t_quotes *data, char *input)
{
	while (*input)
	{
		if ((*input == '\'' && !data->in_dquotes)
			|| (*input == '\"' && !data->in_squotes))
		{
			if (*input == '\'')
				data->in_squotes = !data->in_squotes;
			else if (*input == '\"')
				data->in_dquotes = !data->in_dquotes;
		}
		else
		{
			data->len++;
			data->result = ft_reallocate(data->result, *input, data->len);
			if (data->result == NULL)
				return (-1);
		}
		input++;
	}
	return (0);
}

char	*handle_quotes_exec(char *input)
{
	t_quotes	data;

	if (input == NULL)
		return (NULL);
	init_data(&data, input);
	if (data.result == NULL)
		return (NULL);
	if (ft_strcmp(input, DQUOTES) == 0 || ft_strcmp(input, SQUOTES) == 0)
		return (data.result);
	if (handle_quotes_main_loop(&data, input) == -1)
	{
		free(data.result);
		return (NULL);
	}
	if (data.in_squotes || data.in_dquotes)
	{
		free(data.result);
		return (ft_strdup(data.original));
	}
	return (data.result);
}
