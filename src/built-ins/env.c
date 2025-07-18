/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:46 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/07 13:25:28 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_env(t_env *env)
{
	char	*line;
	char	*tmp;

	while (env)
	{
		if (env->value)
		{
			line = ft_strjoin(env->key, "=");
			if (!line)
				return (EXIT_FAILURE);
			tmp = ft_strjoin(line, env->value);
			free(line);
			if (!tmp)
				return (EXIT_FAILURE);
			ft_putendl_fd(tmp, STDOUT_FILENO);
			free(tmp);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_env(t_shell *data, char **args)
{
	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	if (!data->env)
		return (EXIT_FAILURE);
	return (print_env(data->env));
}
