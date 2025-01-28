/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:54:22 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/12 08:05:01 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*map;
	t_list	*new_elem;

	if (!lst || !f)
		return (NULL);
	temp = lst;
	map = NULL;
	while (temp)
	{
		new_elem = (t_list *)malloc(sizeof(t_list));
		if (!new_elem)
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		new_elem->content = f(temp->content);
		new_elem->next = NULL;
		ft_lstadd_back(&map, new_elem);
		temp = temp->next;
	}
	return (map);
}
