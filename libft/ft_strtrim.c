/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:46:58 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/02 12:03:07 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

static int	setchar(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	size_t		new_len;
	char		*trimmed_str;

	start = s1;
	while (setchar(*start, set))
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && setchar(*end, set))
		end--;
	new_len = end - start + 2;
	trimmed_str = (char *)malloc(new_len);
	if (trimmed_str == NULL)
		return (NULL);
	ft_strlcpy(trimmed_str, start, new_len);
	trimmed_str[new_len - 1] = '\0';
	return (trimmed_str);
}
