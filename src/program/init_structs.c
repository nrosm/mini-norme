/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:30:25 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/05 13:36:52 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_tokens(void)
{
	t_token	*tokens;

	tokens = (t_token *)malloc(sizeof(t_token));
	if (!tokens)
		return (NULL);
	tokens->token_type = T_ARGV;
	tokens->value = NULL;
	tokens->next = NULL;
	return (tokens);
}

t_env	*init_env(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
	return (env);
}

t_shell	*init_minishell(void)
{
	t_shell	*minishell;

	minishell = (t_shell *)malloc(sizeof(t_shell));
	if (!minishell)
		return (NULL);
	minishell->input = NULL;
	minishell->status = 0;
	minishell->tokens = NULL;
	minishell->commands = NULL;
	minishell->env = init_env();
	if (!minishell->env)
	{
		free(minishell);
		return (NULL);
	}
	return (minishell);
}
