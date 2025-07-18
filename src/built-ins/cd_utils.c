/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:28:15 by nroson-m          #+#    #+#             */
/*   Updated: 2025/07/07 13:32:23 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/structs.h"

void	set_env(t_env **env, const char *key, const char *value)
{
	t_env	*tmp;

	tmp = *env;
	if (!key || !value)
		return ;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new_env(env, (char *)key, (char *)value);
}

char	*get_env_value(t_env *env, const char *key)
{
	if (!key)
		return (NULL);
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_cd_target(t_shell *env, char *arg)
{
	char	*home;

	if (!arg)
	{
		home = get_env(env->env, "HOME");
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (NULL);
		}
		return (home);
	}
	return (arg);
}

char	*get_current_directory(char *cwd)
{
	if (!getcwd(cwd, PATH_MAX))
	{
		perror("cd (getcwd)");
		return (NULL);
	}
	return (cwd);
}
