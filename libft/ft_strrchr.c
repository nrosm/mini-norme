/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:51:46 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/06 16:06:01 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		size;
	char	*p1;

	p1 = (char *)s;
	size = ft_strlen(s);
	while (size >= 0)
	{
		if (p1[size] == (char)c)
		{
			return (&p1[size]);
		}
		size--;
	}
	return (0);
}
