/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:33:28 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/22 11:34:53 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char(char c, int *len)
{
	ft_putchar_fd(c, 1);
	(*len)++;
}

void	ft_print_str(char *str, int *len)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		(*len) += 6;
		return ;
	}
	else
	{
		ft_putstr_fd(str, 1);
		(*len) += ft_strlen(str);
	}
}

void	ft_print_ptr(void *ptr, int *len, char *hex_digits)
{
	size_t	addr;

	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		(*len) += 5;
		return ;
	}
	else
	{
		addr = (size_t)ptr;
		ft_putstr_fd("0x", 1);
		(*len) += 2;
		ft_puthex(addr, len, hex_digits);
	}
}
