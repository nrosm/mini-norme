/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:01:35 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/07 13:17:39 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/structs.h"

static void	free_node(t_env *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

static int	unset_next_node(char *key, t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		if (env->next->key && ft_strcmp(key, env->next->key) == 0)
		{
			tmp = env->next;
			env->next = tmp->next;
			free_node(tmp);
			return (0);
		}
		env = env->next;
	}
	return (0);
}

int	ft_unset(char **a, t_shell *data)
{
	t_env	*env;
	t_env	*tmp;

	if (!a[1])
		return (0);
	env = data->env;
	if (!env)
		return (0);
	if (env->key && ft_strcmp(a[1], env->key) == 0)
	{
		tmp = env->next;
		free_node(env);
		data->env = tmp;
		return (0);
	}
	return (unset_next_node(a[1], env));
}
