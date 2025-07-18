/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:32:13 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 14:32:16 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_redirection_target(t_command *cmd,
			t_token *token, char *value)
{
	char	**target;

	target = NULL;
	if (token->token_type == T_REDIRECT_IN)
		target = &cmd->infile;
	else if (token->token_type == T_REDIRECT_OUT)
		target = &cmd->outfile;
	else if (token->token_type == T_APPEND)
		target = &cmd->append;
	if (target)
	{
		free(*target);
		*target = value;
	}
	else if (token->token_type == T_PIPE)
	{
		cmd->pipe = 1;
		free(value);
	}
	else if (token->token_type == T_HEREDOC)
	{
		cmd->heredoc = 1;
		free(value);
	}
}

void	update_command(t_command *cmd, t_token *token)
{
	char	*value;

	if (!token->next)
		return ;
	value = ft_strdup(token->next->value);
	if (!value)
		return ;
	assign_redirection_target(cmd, token, value);
}

void	add_args_command(t_command *command, char *token)
{
	int		i;
	int		j;
	int		count;
	char	**new_argv;

	i = 0;
	j = 0;
	count = 0;
	while (command->argv && command->argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return ;
	while (i < count)
	{
		new_argv[i] = ft_strdup(command->argv[i]);
		i++;
	}
	new_argv[i++] = ft_strdup(token);
	new_argv[i] = NULL;
	while (j < count)
		free(command->argv[j++]);
	free(command->argv);
	command->argv = new_argv;
}

int	command_empty(t_command *command)
{
	return (!command->argv && !command->infile && !command->heredoc
		&& !command->outfile);
}

void	add_command_list(t_command **commands, t_command *new)
{
	t_command	*temporal;

	if (!new || command_empty(new))
	{
		free_command(new);
		return ;
	}
	if (!*commands)
	{
		*commands = new;
		return ;
	}
	temporal = *commands;
	while (temporal->next)
		temporal = temporal->next;
	temporal->next = new;
}
