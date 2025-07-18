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

int	is_var(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static char	*extract_and_expand(const char *input,
	size_t *i, t_expand_ctx *ctx)
{
	size_t	start;

	(*i)++;
	start = *i;
	if (!input[start])
		return (ft_strdup("$"));
	if (input[start] == '?')
	{
		(*i)++;
		return (get_var_value("?", ctx));
	}
	return (handle_var_expand(input, start, i, ctx));
}

static void	update_quotes(const char *input, size_t i,
	int *squote, int *dquote)
{
	if (input[i] == '\'' && !(*dquote))
		*squote = !(*squote);
	else if (input[i] == '"' && !(*squote))
		*dquote = !(*dquote);
}

static char	*expand_loop(const char *input,
	t_expand_ctx *ctx, char *result)
{
	size_t	i;
	int		squote;
	int		dquote;
	char	tmp[2];

	i = 0;
	squote = 0;
	dquote = 0;
	while (input[i])
	{
		update_quotes(input, i, &squote, &dquote);
		if (input[i] == '$' && !squote
			&& (is_var(input[i + 1]) || input[i + 1] == '?'))
			result = ft_strjoin_free(result,
					extract_and_expand(input, &i, ctx), 3);
		else
		{
			tmp[0] = input[i];
			tmp[1] = '\0';
			i++;
			result = ft_strjoin_free(result, ft_strdup(tmp), 3);
		}
	}
	return (result);
}

char	*expand_variables(const char *input, t_env *env, int last_status)
{
	t_expand_ctx	ctx;
	char			*result;

	ctx.env = env;
	ctx.last_status = last_status;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (expand_loop(input, &ctx, result));
}
