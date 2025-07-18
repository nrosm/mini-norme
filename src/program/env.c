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

char	*get_value(char *env)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (ft_strdup(""));
	return (ft_strdup(env + i + 1));
}

static int	init_env_node(t_env **new, char *key, char *value)
{
	*new = (t_env *)malloc(sizeof(t_env));
	if (!(*new))
		return (0);
	ft_memset(*new, 0, sizeof(t_env));
	(*new)->key = ft_strdup(key);
	if (!(*new)->key)
	{
		free(*new);
		return (0);
	}
	(*new)->value = ft_strdup(value);
	if (!(*new)->value)
	{
		free((*new)->key);
		free(*new);
		return (0);
	}
	(*new)->next = NULL;
	return (1);
}

void	new_env(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*temporal;

	if (!init_env_node(&new, key, value))
		return ;
	if (!(*env))
		*env = new;
	else
	{
		temporal = *env;
		while (temporal->next)
			temporal = temporal->next;
		temporal->next = new;
	}
}

void	get_variables(t_env **env, char **envp)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		if (key && value)
		{
			new_env(env, key, value);
			free(key);
			free(value);
		}
		else
		{
			free(key);
			free(value);
		}
		i++;
	}
}

char	*get_env(t_env *env, const char *key)
{
	while (env)
	{
		if (env->key && env->value && ft_strncmp(env->key, key, ft_strlen(key)
				+ 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
