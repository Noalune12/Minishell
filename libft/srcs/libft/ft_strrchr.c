/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:55:37 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/12 07:37:02 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s[s_len] == '\0' && (unsigned char)c == '\0')
		return ((char *)(s + s_len));
	while (s_len--)
	{
		if (s[s_len] == (unsigned char)c)
			return ((char *)(s + s_len));
	}
	return (NULL);
}
