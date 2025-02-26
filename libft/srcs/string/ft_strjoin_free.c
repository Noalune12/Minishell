/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:52:11 by gueberso          #+#    #+#             */
/*   Updated: 2025/02/26 19:17:01 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/**
 * @brief Joins two strings and optionally frees the originals.
 *
 * Allocates and returns a new string resulting from the concatenation of
 * `*s1` and `*s2`.
 * Frees `*s1` and/or `*s2` if `first` and `second` are true, respectively.
 *
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @param first Free `*s1` if true.
 * @param second Free `*s2` if true.
 * @return Pointer to the new string, or NULL on allocation failure.
 */
char	*ft_strjoin_free(char **s1, char **s2, bool first, bool second)
{
	char	*res;
	char	*s1_temp;
	char	*s2_temp;
	ssize_t	i;

	s1_temp = *s1;
	s2_temp = *s2;
	res = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(*s2) + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (*s1_temp)
		res[++i] = *s1_temp++;
	while (*s2_temp)
		res[++i] = *s2_temp++;
	res[++i] = '\0';
	if (first)
		free(*s1);
	if (second)
		free(*s2);
	return (res);
}
