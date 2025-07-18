/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:27:52 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 14:27:54 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_spaces(char *input)
{
	int		i;
	int		end;
	int		len_input;
	char	*new_string;

	new_string = NULL;
	if (!input)
		return (NULL);
	i = 0;
	len_input = ft_strlen(input);
	end = len_input - 1;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	while (end >= i && (input[end] == ' ' || input[end] == '\t'))
		end--;
	if (i > end)
		return (ft_strdup(""));
	new_string = ft_substr(input, i, end - i + 1);
	return (new_string);
}

void	normalize_spaces(char *input)
{
	int		i;
	int		j;
	char	buffer[9999];
	int		is_space;

	i = 0;
	j = 0;
	is_space = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
		{
			if (is_space == 0)
				buffer[j++] = ' ';
			is_space = 1;
		}
		else
		{
			buffer[j++] = input[i];
			is_space = 0;
		}
		i++;
	}
	buffer[j] = '\0';
	strcpy(input, buffer);
}

void	quotes_manage(char *input)
{
	int	i;
	int	state_quote;

	i = 0;
	state_quote = 0;
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && state_quote == 0)
			state_quote = 1;
		else if ((input[i] == '"' || input[i] == '\'') && state_quote == 1)
			state_quote = 0;
		else if (input[i] == ' ' && state_quote)
			input[i] = '\x01';
		i++;
	}
}

void	restore_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\x01')
			input[i] = ' ';
		i++;
	}
}

void	pre_process(t_shell *shell)
{
	char	*string;

	if (!shell || !shell->input)
		return ;
	string = remove_spaces(shell->input);
	if (!string)
	{
		free(shell->input);
		shell->input = NULL;
		return ;
	}
	quotes_manage(string);
	normalize_spaces(string);
	restore_quotes(string);
	free(shell->input);
	shell->input = string;
}
