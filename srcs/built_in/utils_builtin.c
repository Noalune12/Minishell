/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:19 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 12:54:57 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	swap_strs(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	free(temp);
}

int	ft_strnlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

int	ascii_cmp(char *a, char *b)
{
	return (ft_strcmp(a, b));
}

static void	swap_data(t_list *a, t_list *b)
{
	char	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void	ft_list_sort(t_list **begin_list, int (*cmp)(char *, char *))
{
	t_list	*list;
	t_list	*next;
	bool	swap;

	if (begin_list == NULL || !cmp)
		return ;
	swap = true;
	while (swap)
	{
		swap = false;
		list = *begin_list;
		while (list->next)
		{
			next = list->next;
			if (cmp(list->content, next->content) > 0)
			{
				swap_data(list, next);
				swap = true;
			}
			list = list->next;
		}
	}
}
