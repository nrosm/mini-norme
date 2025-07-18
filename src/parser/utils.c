/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:32:23 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 14:32:25 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_invalid_start_token(t_token *token)
{
	return (!token || token->token_type == T_PIPE
		|| token->token_type == T_REDIRECT_IN
		|| token->token_type == T_REDIRECT_OUT
		|| token->token_type == T_APPEND
		|| token->token_type == T_HEREDOC);
}

int	has_invalid_sequence(t_token *current)
{
	t_token	*next;

	while (current)
	{
		next = current->next;
		if ((current->token_type == T_PIPE && (!next
					|| next->token_type == T_PIPE))
			|| ((current->token_type == T_REDIRECT_IN
					|| current->token_type == T_REDIRECT_OUT
					|| current->token_type == T_APPEND
					|| current->token_type == T_HEREDOC) && (!next
					|| (next->token_type != T_ARGV
						&& next->token_type != T_COMMAND))))
			return (1);
		if (!next && (current->token_type == T_PIPE
				|| current->token_type == T_REDIRECT_IN
				|| current->token_type == T_REDIRECT_OUT
				|| current->token_type == T_APPEND
				|| current->token_type == T_HEREDOC))
			return (1);
		current = current->next;
	}
	return (0);
}

int	can_execute(t_token *tokens)
{
	if (is_invalid_start_token(tokens))
		return (0);
	if (has_invalid_sequence(tokens))
		return (0);
	return (1);
}

void	copy_without_quotes(const char *arg, char *result)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			quote = arg[i++];
			while (arg[i] && arg[i] != quote)
				result[j++] = arg[i++];
			if (arg[i] == quote)
				i++;
		}
		else
			result[j++] = arg[i++];
	}
	result[j] = '\0';
}

char	*remove_quotes(const char *arg)
{
	char	*result;
	size_t	len;

	if (!arg)
		return (NULL);
	len = ft_strlen(arg);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	copy_without_quotes(arg, result);
	return (result);
}
