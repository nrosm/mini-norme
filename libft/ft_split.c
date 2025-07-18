/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:53:42 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/06 16:12:44 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

static int	count_strings(char const *string, char chr)
{
	int	count_strings;
	int	in_substring;

	count_strings = 0;
	in_substring = 0;
	while (*string != '\0')
	{
		if (*string != chr && in_substring == 0)
		{
			in_substring = 1;
			count_strings++;
		}
		else if (*string == chr)
			in_substring = 0;
		string++;
	}
	return (count_strings);
}

static void	free_memory(char **array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**while_substr(char const *s, char c, char **substr, int *i)
{
	int	start;
	int	j;

	j = 0;
	while (s[*i] != '\0')
	{
		while (s[*i] == c)
			(*i)++;
		start = *i;
		while (s[*i] != c && s[*i] != '\0')
			(*i)++;
		if (*i > start)
		{
			substr[j] = (char *)malloc((*i - start + 1) * sizeof(char));
			if (substr[j] == NULL)
			{
				free_memory(substr, j);
				return (NULL);
			}
			ft_strlcpy(substr[j], &s[start], *i - start + 1);
			j++;
		}
	}
	substr[j] = NULL;
	return (substr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**substr;

	i = 0;
	if (!s)
		return (NULL);
	substr = (char **)malloc((count_strings(s, c) + 1) * sizeof(char *));
	if (!substr)
		return (NULL);
	return (while_substr(s, c, substr, &i));
}
