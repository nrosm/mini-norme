/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:12 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/11/09 17:35:13 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdarg.h>

static int	case_print(va_list args, const char format)
{
	int	len_print;

	len_print = 0;
	if (format == 'c')
		len_print += ft_putchar(va_arg(args, int));
	else if (format == 's')
		len_print += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		len_print += ft_putptr(va_arg(args, void *));
	else if (format == 'd')
		len_print += ft_putdouble(va_arg(args, int));
	else if (format == 'i')
		len_print += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		len_print += ft_putunsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		len_print += ft_puthexa(va_arg(args, unsigned int));
	else if (format == 'X')
		len_print += ft_puthexa_mayus(va_arg(args, unsigned int));
	else if (format == '%')
		len_print += ft_putporcent();
	return (len_print);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		length_print;
	va_list	args;

	i = 0;
	length_print = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			length_print += case_print(args, format[i + 1]);
			i++;
		}
		else
			length_print += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (length_print);
}
