/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:01:12 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/07 13:28:57 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/structs.h"

bool	is_valid_env_var_key(char *var)
{
	int	i;

	i = 0;
	if (!var || (ft_isalpha(var[i]) == 0 && var[i] != '_'))
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

t_env	*get_env_var(t_env *env, char *key)
{
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_export(t_shell *data, char **args)
{
	int		i;
	int		ret;
	char	**tmp;

	i = 1;
	ret = EXIT_SUCCESS;
	if (!args[i])
		return (ft_env(data, NULL));
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			errmsg_cmd("export", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '='))
		{
			tmp = get_key_value_pair(args[i]);
			if (tmp && tmp[0])
				set_env_var(data, tmp[0], tmp[1]);
			free_str_tab(tmp);
		}
		i++;
	}
	return (ret);
}
