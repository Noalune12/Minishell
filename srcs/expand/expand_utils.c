/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:32 by lbuisson          #+#    #+#             */
/*   Updated: 2025/05/20 14:30:53 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"

char	*ft_getenv(char *var_name, t_list *env, int *error)
{
	char	*var;
	t_list	*temp;
	int		len;

	var = ft_strjoin(var_name, "=");
	if (var == NULL)
	{
		*error = 1;
		return (NULL);
	}
	temp = env;
	len = ft_strlen(var);
	while (temp)
	{
		if (ft_strncmp(temp->content, var, len) == 0)
		{
			free(var);
			return (temp->content + len);
		}
		temp = temp->next;
	}
	free(var);
	return (NULL);
}

void	copy_var_value(char *var_name, t_expand_data *data)
{
	char	*var_value;

	var_value = ft_getenv(var_name, data->env, 0);
	if (var_value)
	{
		while (*var_value)
		{
			data->expanded[data->j] = *var_value;
			data->j++;
			var_value++;
		}
	}
}
