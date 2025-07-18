/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:57:36 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/02 11:52:19 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char		*str;
	size_t		length;

	if (!s)
		return (ft_strdup(""));
	length = ft_strlen(s) + 1;
	str = (char *) malloc(length * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, length);
	return (str);
}
