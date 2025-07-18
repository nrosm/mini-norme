/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:50:39 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/02 11:36:09 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char		*source;
	unsigned char			*dst;
	size_t					i;

	dst = (unsigned char *)dest;
	source = (const unsigned char *)src;
	i = 0;
	while (dst == src || !n)
		return (dest);
	while (i < n)
	{
		dst[i] = source[i];
		i++;
	}
	return (dest);
}
