/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:51:05 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/02 11:39:55 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*source;

	i = 0;
	dst = (unsigned char *)dest;
	source = (unsigned char *)src;
	while (dst == source || !n)
		return (dest);
	if (dst > source && dst < source + n)
	{
		while (n > 0)
		{
			dst[n - 1] = source[n - 1];
			n--;
		}
	}
	while (i < n)
	{
		dst[i] = source[i];
		i++;
	}
	return (dest);
}
