/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:30:08 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/05 14:41:59 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

char	*get_key(char *env)
{
	int		i;
	char	*set_key;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	set_key = malloc(i + 1);
	if (!set_key)
		return (NULL);
	ft_strlcpy(set_key, env, i + 1);
	return (set_key);
}
