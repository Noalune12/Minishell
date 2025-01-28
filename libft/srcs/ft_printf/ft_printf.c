/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:41:21 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/12 11:59:15 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_specifier(char spec)
{
	if (spec == '\0')
		return (-1);
	if (ft_strchr("cspdiuxX%", spec))
		return (1);
	return (0);
}

static void	ft_print_spec(char spec, va_list *args, int *len)
{
	if (spec == 'c')
		ft_print_char(va_arg(*args, int), len);
	else if (spec == 's')
		ft_print_str(va_arg(*args, char *), len);
	else if (spec == 'p')
		ft_print_ptr(va_arg(*args, void *), len, "0123456789abcdef");
	else if (spec == 'd' || spec == 'i')
		ft_print_nbr(va_arg(*args, int), len);
	else if (spec == 'u')
		ft_print_unbr(va_arg(*args, unsigned int), len);
	else if (spec == 'x')
		ft_print_hexa(va_arg(*args, unsigned int), len, "0123456789abcdef");
	else if (spec == 'X')
		ft_print_hexa(va_arg(*args, unsigned int), len, "0123456789ABCDEF");
	else if (spec == '%')
		ft_print_char('%', len);
}

static int	ft_parse_printf(const char *fmt, va_list *args, int *len)
{
	while (*fmt)
	{
		if (*fmt == '%')
		{
			if (ft_check_specifier(*(fmt + 1)) == 1)
			{
				fmt++;
				ft_print_spec(*fmt, args, len);
			}
			else if (ft_check_specifier(*(fmt + 1)) == -1
				|| ft_check_specifier(*(fmt + 1)) == 0)
				return (-1);
		}
		else
			ft_print_char(*fmt, len);
		fmt++;
	}
	return (1);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		len;

	if (!fmt)
		return (-1);
	va_start(args, fmt);
	len = 0;
	if (ft_parse_printf(fmt, &args, &len) == -1)
	{
		va_end(args);
		return (-1);
	}
	va_end(args);
	return (len);
}
