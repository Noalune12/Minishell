/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:52:11 by gueberso          #+#    #+#             */
/*   Updated: 2025/02/28 18:35:20 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/**
 * @brief Concatenates two strings and frees the second string
 *
 * This function joins two strings (s1 and s2) into a newly allocated string.
 * After the concatenation is complete, the memory allocated for the second
 * string (s2) is automatically freed.
 *
 * @param s1 The first string to be concatenated (preserved)
 * @param s2 The second string to be concatenated (will be freed)
 * @return A newly allocated string containing the concatenation of s1 and s2,
 *         or NULL if memory allocation fails or if either input is NULL
 *
 * @warning The second parameter (s2) will be freed inside this function,
 *          so it must be heap-allocated and should not be used after calling
 *          this function.
 */
char	*ft_strjoin_free(const char *s1, char *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < s1_len)
		res[i++] = s1[j++];
	j = 0;
	while (j < s2_len)
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s2);
	return (res);
}
