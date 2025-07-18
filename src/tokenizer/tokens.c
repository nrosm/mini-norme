/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:27:36 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/07 13:38:13 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type(char *token)
{
	if (is_command(token))
		return (T_COMMAND);
	if (ft_strcmp("|", token) == 0)
		return (T_PIPE);
	if (ft_strcmp("<", token) == 0)
		return (T_REDIRECT_IN);
	if (ft_strcmp("<<", token) == 0)
		return (T_HEREDOC);
	if (ft_strcmp(">", token) == 0)
		return (T_REDIRECT_OUT);
	if (ft_strcmp(">>", token) == 0)
		return (T_APPEND);
	if (token[0] == '-' && token[1] != '\0' && token[1] != '-')
		return (T_FLAG);
	return (T_ARGV);
}

void	token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

static char	*extract_next_token(char *input, int *i)
{
	int		start;
	char	quote;
	int		j;

	while (input[*i] == ' ')
		(*i)++;
	start = *i;
	quote = 0;
	j = *i;
	while (input[j])
	{
		if ((input[j] == '\'' || input[j] == '"') && quote == 0)
			quote = input[j];
		else if (input[j] == quote)
			quote = 0;
		else if (input[j] == ' ' && quote == 0)
			break ;
		j++;
	}
	*i = j;
	return (ft_substr(input, start, j - start));
}

static void	process_token(char *input, int *i, t_token **tokens)
{
	t_token			*new_token;
	t_token_type	type;
	char			*token_str;
	char			*cleaned;

	token_str = extract_next_token(input, i);
	if (!token_str || token_str[0] == '\0')
	{
		free(token_str);
		return ;
	}
	cleaned = remove_quotes(token_str);
	free(token_str);
	type = get_token_type(cleaned);
	new_token = create_token(cleaned, type);
	free(cleaned);
	token_lstadd_back(tokens, new_token);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
		process_token(input, &i, &tokens);
	return (tokens);
}
