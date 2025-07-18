/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:34:46 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/11/04 17:34:48 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_puthexa(unsigned int number)
{
	int		i;
	int		nibble;
	int		len;
	char	hex[16] = "0123456789abcdef";
	char	buffer[16];

	if (number == 0)
		return (ft_putchar('0'));
	i = 0;
	len = 0;
	while (number > 0)
	{
		nibble = number % 16;
		buffer[i++] = hex[nibble];
		number /= 16;
	}
	while (i > 0)
		len += ft_putchar(buffer[--i]);
	return (len);
}

int	ft_puthexa_mayus(unsigned int number)
{
	int		i;
	int		nibble;
	int		len;
	char	hex[16] = "0123456789ABCDEF";
	char	buffer[16];

	if (number == 0)
		return (ft_putchar('0'));
	i = 0;
	len = 0;
	while (number > 0)
	{
		nibble = number % 16;
		buffer[i++] = hex[nibble];
		number /= 16;
	}
	while (i > 0)
		len += ft_putchar(buffer[--i]);
	return (len);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int change_hexa = 0;
// 	int *pointer = &change_hexa;
// 	ft_puthexa((unsigned long)pointer);
// 	printf("\n%p", (void *)pointer);
// 	return (0);
// }