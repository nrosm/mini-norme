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

void	clean_arguments(t_command *cmd)
{
	int		i;
	char	*cleaned;

	if (!cmd || !cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		cleaned = remove_quotes(cmd->argv[i]);
		free(cmd->argv[i]);
		cmd->argv[i] = cleaned;
		i++;
	}
}

void	expand_token(t_token *token, t_env *env, int status)
{
	char	*expanded;
	char	*cleaned;
	size_t	len;

	if (!token || !token->value)
		return ;
	len = ft_strlen(token->value);
	if ((token->value[0] == '\'' && token->value[len - 1] == '\''))
	{
		cleaned = remove_quotes(token->value);
		free(token->value);
		token->value = cleaned;
		return ;
	}
	expanded = expand_variables(token->value, env, status);
	if (token->value[0] == '"' && token->value[len - 1] == '"')
	{
		free(token->value);
		token->value = expanded;
		return ;
	}
	cleaned = remove_quotes(expanded);
	free(token->value);
	free(expanded);
	token->value = cleaned;
}

static void	handle_token_logic(t_command *command, t_token *token,
	t_token_type prev_type)
{
	if (token->token_type == T_COMMAND || token->token_type == T_ARGV
		|| token->token_type == T_FLAG)
	{
		if (prev_type != T_REDIRECT_IN && prev_type != T_REDIRECT_OUT
			&& prev_type != T_APPEND && prev_type != T_HEREDOC)
			add_args_command(command, token->value);
	}
	else
		update_command(command, token);
}

static int	handle_token_redirects(t_command **commands, t_command **command,
	t_token *token, t_shell *shell)
{
	int	fd;

	if (token->token_type == T_PIPE)
	{
		add_command_list(commands, *command);
		*command = create_command();
		if (!*command)
		{
			free_command_list(*commands);
			return (1);
		}
	}
	else if (token->token_type == T_HEREDOC)
	{
		fd = create_heredoc(token->next->value, shell->env);
		if (fd == -1)
			return (1);
		(*command)->heredoc = fd;
	}
	return (0);
}

void	parser(t_command **commands, t_token *tokens, t_shell *shell)
{
	t_command		*command;
	t_token_type	prev_type;
	int				added;

	if (!tokens || !can_execute(tokens))
		return ;
	command = create_command();
	if (!command)
		return ;
	prev_type = -1;
	while (tokens)
	{
		expand_token(tokens, shell->env, shell->status);
		handle_token_logic(command, tokens, prev_type);
		if (handle_token_redirects(commands, &command, tokens, shell))
			return ;
		added = (tokens->token_type == T_PIPE);
		prev_type = tokens->token_type;
		tokens = tokens->next;
	}
	if (command && !added)
		add_command_list(commands, command);
	else
		free_command(command);
}
