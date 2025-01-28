/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:48:34 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/12 08:03:14 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*temp2;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	while (temp)
	{
		temp2 = temp->next;
		if (del)
			del(temp->content);
		free(temp);
		temp = temp2;
	}
	*lst = NULL;
}
