/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:40:10 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/12 13:50:11 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checknptr(long long nb, int sign, size_t i, const char *nptr)
{
	if ((long)nb > (LONG_MAX - (nptr[i] + '0')) / 10)
	{
		if (sign == -1)
			return (0);
		else if (sign == 1)
			return (-1);
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int				sign;
	long long		res;
	size_t			i;

	sign = 1;
	res = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (ft_checknptr(res, sign, i, nptr) == 0)
			return (0);
		else if (ft_checknptr(res, sign, i, nptr) == -1)
			return (-1);
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return ((int)(res * sign));
}
