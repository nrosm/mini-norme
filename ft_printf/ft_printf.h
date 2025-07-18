/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:25:18 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/11/09 17:25:20 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	ft_putchar(char c);
int	ft_putporcent(void);
int	ft_putptr(void *pointer);
int	ft_puthexa(unsigned int number);
int	ft_puthexa_mayus(unsigned int number);
int	ft_putnbr(int n);
int	ft_putdouble(float number);
int	ft_putstr(char *s);
int	ft_printf(const char *format, ...);
int	ft_putunsigned(unsigned int number);

#endif