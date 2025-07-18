/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:26:06 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/02 11:42:25 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	char		*string;
	char		new_char;
	size_t		i;

	string = (char *)s;
	new_char = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		string[i] = new_char;
		i++;
	}
	return (s);
}
