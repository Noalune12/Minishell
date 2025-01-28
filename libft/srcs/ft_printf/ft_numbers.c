/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:33:17 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/25 07:36:16 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_nbr(int nb, int *len)
{
	ft_putnbr_fd(nb, 1);
	if (nb == -2147483648)
	{
		(*len) += 11;
		return ;
	}
	if (nb < 0)
	{
		nb = -nb;
		(*len)++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		(*len)++;
	}
	(*len)++;
}

void	ft_print_unbr(unsigned int nb, int *len)
{
	if (nb >= 10)
	{
		ft_print_unbr(nb / 10, len);
	}
	ft_print_char(nb % 10 + '0', len);
}

void	ft_puthex(size_t nbr, int *len, char *hex_digits)
{
	if (nbr >= 16)
		ft_puthex(nbr / 16, len, hex_digits);
	ft_print_char(hex_digits[nbr % 16], len);
}

void	ft_print_hexa(unsigned int hex, int *len, char *hex_digits)
{
	if (hex == 0)
	{
		ft_print_char('0', len);
		return ;
	}
	else
		ft_puthex(hex, len, hex_digits);
}
