/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:46:07 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/13 13:19:12 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	unsigned const char	*str;
	size_t				i;

	if (!dest && !src)
		return (dest);
	dst = (unsigned char *)dest;
	str = (unsigned const char *)src;
	i = 0;
	if (dst < str)
	{
		while (i < n)
		{
			dst[i] = str[i];
			i++;
		}
	}
	else
	{
		while (i < n--)
			dst[n] = str[n];
	}
	return (dest);
}
