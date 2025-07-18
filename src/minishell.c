/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:26:38 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 14:26:42 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_global_state	g_minishell = {
	.context = 0,
	.status = 0,
	.trigered = 0
};

static void	process_and_execute(t_shell *minishell)
{
	t_command	*cmd;

	pre_process(minishell);
	minishell->tokens = lexer(minishell->input);
	minishell->commands = NULL;
	parser(&minishell->commands, minishell->tokens, minishell);
	if (minishell->commands)
	{
		cmd = minishell->commands;
		while (cmd)
		{
			clean_arguments(cmd);
			cmd = cmd->next;
		}
		executor(minishell);
	}
	free(minishell->input);
	free_tokens(minishell->tokens);
	free_command_list(minishell->commands);
}

static void	run_minishell_loop(t_shell *minishell)
{
	while (1)
	{
		minishell->input = readline(
				"\033[1;34m⮞ "
				"\033[1;36m[minishell]"
				"\033[1;34m ⮜ "
				"\033[0;32mready$ "
				"\033[0m");
		if (!minishell->input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (minishell->input[0] != '\0')
			add_history(minishell->input);
		process_and_execute(minishell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*minishell;

	(void)argc;
	(void)argv;
	minishell = init_minishell();
	if (!minishell)
		return (1);
	get_variables(&minishell->env, envp);
	init_signals();
	run_minishell_loop(minishell);
	free_env_list(minishell->env);
	free(minishell);
	return (0);
}
