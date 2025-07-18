/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:51:06 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/11/13 11:51:07 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <unistd.h>

int	ft_putptr(void *pointer)
{
	int					i;
	int					len;
	int					nibble;
	char				hex[] = "0123456789abcdef";
	char				buffer[16];
	unsigned long long	ptr;

	if (pointer == NULL)
	{
		len = ft_putstr("0x0");
		return (len);
	}
	i = 0;
	ptr = (unsigned long long)pointer;
	len = ft_putstr("0x");
	while (ptr > 0)
	{
		nibble = ptr % 16;
		buffer[i++] = hex[nibble];
		ptr /= 16;
	}
	while (i > 0)
		len += ft_putchar(buffer[--i]);
	return (len);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	change_hexa;
// 	int	*pointer;

// 	change_hexa = 0;
// 	pointer = &change_hexa;
// 	ft_putpointer((unsigned long)pointer);
// 	printf("\n%p", (void *)pointer);
// 	return (0);
// }
