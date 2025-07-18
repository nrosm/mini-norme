/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:29:00 by nroson-m          #+#    #+#             */
/*   Updated: 2025/07/07 13:29:45 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/structs.h"

bool	append_env_var(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (false);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!*env)
	{
		*env = new_node;
	}
	else
	{
		temp = *env;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	return (true);
}

bool	set_env_var(t_shell *data, char *key, char *value)
{
	t_env	*existing;

	existing = get_env_var(data->env, key);
	if (existing)
	{
		free_ptr(existing->value);
		existing->value = ft_strdup(value);
		return (true);
	}
	return (append_env_var(&data->env, key, value));
}

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free_ptr(tab[i]);
		i++;
	}
	free(tab);
}

char	**get_key_value_pair(char *argv)
{
	char	**tmp;
	char	*equal_sign;

	equal_sign = ft_strchr(argv, '=');
	if (!equal_sign)
		return (NULL);
	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		return (NULL);
	tmp[0] = ft_substr(argv, 0, equal_sign - argv);
	tmp[1] = ft_strdup(equal_sign + 1);
	tmp[2] = NULL;
	return (tmp);
}
