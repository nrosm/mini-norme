/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/07/17 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(const char *key, t_expand_ctx *ctx)
{
	char	*val;

	if (!key)
		return (ft_strdup(""));
	if (ft_strncmp(key, "?", 2) == 0)
		return (ft_itoa(ctx->last_status));
	val = get_env_value(ctx->env, key);
	if (val)
		return (ft_strdup(val));
	return (ft_strdup(""));
}

char	*handle_var_expand(const char *input,
	size_t start, size_t *i, t_expand_ctx *ctx)
{
	size_t	len;
	char	*name;
	char	*val;

	len = 0;
	while (input[start + len] && is_var(input[start + len]))
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	name = ft_substr(input, start, len);
	if (!name)
		return (ft_strdup(""));
	val = get_var_value(name, ctx);
	free(name);
	*i += len;
	return (val);
}

int	is_quoted(const char *str)
{
	size_t	length;

	length = ft_strlen(str);
	if (!length)
		return (0);
	if ((str[0] == '\'' && str[length - 1] == '\'') || (str[0] == '"'
			&& str[length - 1] == '"'))
		return (1);
	return (0);
}

t_command	*create_command(void)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->argv = NULL;
	new_command->infile = NULL;
	new_command->outfile = NULL;
	new_command->append = NULL;
	new_command->heredoc = 0;
	new_command->pipe = 0;
	new_command->next = NULL;
	return (new_command);
}
