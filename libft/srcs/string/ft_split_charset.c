/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:11:26 by lbuisson          #+#    #+#             */
/*   Updated: 2025/05/20 14:13:59 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char c, char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	countwords(char const *s, char *charset)
{
	size_t	count;
	size_t	i;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		if ((ft_is_charset(s[i], charset) == 0
				&& ft_is_charset(s[i + 1], charset) == 1)
			|| (!s[i + 1] && ft_is_charset(s[i], charset) == 0))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_createstr(const char *s, char *charset, size_t *index)
{
	char	*str;
	size_t	i;
	size_t	index_temp;
	size_t	len;

	index_temp = *index;
	len = 0;
	while (ft_is_charset(s[index_temp], charset) == 0 && s[index_temp])
	{
		index_temp++;
		len++;
	}
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[*index];
		(*index)++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	ft_free(char **split)
{
	size_t	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			split[i] = NULL;
			i++;
		}
		free (split);
	}
}

char	**ft_split_charset(char const *s, char *charset)
{
	char	**split;
	size_t	count;
	size_t	index;
	size_t	j;

	count = countwords(s, charset);
	split = (char **)malloc((count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	index = 0;
	j = 0;
	while (count > j)
	{
		while (ft_is_charset(s[index], charset) == 1)
			index++;
		split[j] = ft_createstr(s, charset, &index);
		if (!split[j])
		{
			ft_free(split);
			return (NULL);
		}
		j++;
	}
	split[j] = NULL;
	return (split);
}
