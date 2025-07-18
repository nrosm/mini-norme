/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:27:23 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/07 13:38:28 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(char *token)
{
	if (ft_strcmp("echo", token) == 0)
		return (1);
	else if (ft_strcmp("cd", token) == 0)
		return (1);
	else if (ft_strcmp("pwd", token) == 0)
		return (1);
	else if (ft_strcmp("export", token) == 0)
		return (1);
	else if (ft_strcmp("unset", token) == 0)
		return (1);
	else if (ft_strcmp("env", token) == 0)
		return (1);
	else if (ft_strcmp("exit", token) == 0)
		return (1);
	return (0);
}

int	is_redirect(char *input)
{
	if (ft_strcmp(">>", input) == 0)
		return (1);
	else if (ft_strcmp(">", input) == 0)
		return (1);
	else if (ft_strcmp("<<", input) == 0)
		return (1);
	else if (ft_strcmp("<", input) == 0)
		return (1);
	else if (ft_strcmp("|", input) == 0)
		return (1);
	return (0);
}

int	check_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && quote == 0)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		i++;
	}
	return (quote == 0);
}

t_token	*create_token(char *token, t_token_type token_type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(token);
	new_token->token_type = token_type;
	new_token->next = NULL;
	return (new_token);
}
