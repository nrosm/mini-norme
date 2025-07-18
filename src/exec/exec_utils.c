/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:33:37 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/05 12:45:08 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int mode)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	join_strings(result, s1, s2, len1);
	if (mode == 1 || mode == 3)
		free(s1);
	if (mode == 2 || mode == 3)
		free(s2);
	return (result);
}

static int	count_env_entries(t_env *envp)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = envp;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static void	fill_env_array(char **env_array, t_env *envp)
{
	t_env	*tmp;
	char	*env_line;
	int		i;

	tmp = envp;
	i = 0;
	while (tmp)
	{
		if (tmp->key && tmp->value)
		{
			env_line = ft_strjoin(tmp->key, "=");
			env_array[i] = ft_strjoin_free(env_line, tmp->value, 1);
			i++;
		}
		tmp = tmp->next;
	}
	env_array[i] = NULL;
}

char	**env_list_to_array(t_env *envp)
{
	char	**env_array;
	int		count;

	count = count_env_entries(envp);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	fill_env_array(env_array, envp);
	return (env_array);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
