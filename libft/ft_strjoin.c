/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:26:11 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/06 16:11:11 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	char	*temp;
	int		len_join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_join = ft_strlen(s1) + ft_strlen(s2);
	strjoin = (char *) malloc((len_join + 1) * sizeof(char));
	if (strjoin == NULL)
		return (NULL);
	ft_strlcpy(strjoin, s1, ft_strlen(s1) + 1);
	temp = strjoin + ft_strlen(s1);
	ft_strlcpy(temp, s2, ft_strlen(s2) + 1);
	return (strjoin);
}
