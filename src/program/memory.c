/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:30:41 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/03 16:24:46 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temporal;

	while (tokens)
	{
		temporal = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = temporal;
	}
}

void	free_command(t_command *commands)
{
	int	i;

	if (!commands)
		return ;
	if (commands->argv)
	{
		i = 0;
		while (commands->argv[i])
			free(commands->argv[i++]);
		free(commands->argv);
		commands->argv = NULL;
	}
	if (commands->infile)
		free(commands->infile);
	if (commands->outfile)
		free(commands->outfile);
	if (commands->append)
		free(commands->append);
}

void	free_command_list(t_command *commands)
{
	t_command	*temporal;

	while (commands)
	{
		temporal = commands->next;
		free_command(commands);
		free(commands);
		commands = temporal;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*temporal;

	while (env)
	{
		temporal = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = temporal;
	}
}

void	free_minishell(t_shell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->input)
		free(minishell->input);
	free_tokens(minishell->tokens);
	free_command_list(minishell->commands);
	free_env_list(minishell->env);
	free(minishell);
}
