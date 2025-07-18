/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:05:02 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/06 16:09:11 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*foundchar;

	i = 0;
	foundchar = (char *)s;
	while (s[i] != '\0')
	{
		if (foundchar[i] == (unsigned char)c)
			return (&foundchar[i]);
		i++;
	}
	if (s[i] == '\0' && (unsigned char)c == '\0')
		return (&foundchar[i]);
	return (NULL);
}
