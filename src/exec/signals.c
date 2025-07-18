/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:34:22 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/03 16:24:00 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int			g_context;

// static void	aux_signals(int signal)
// {
// 	(void)signal;
// 	if (g_context == 3)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		g_context = 4;
// 	}
// }

// static void	handle_signals(int signal)
// {
// 	(void)signal;
// 	if (g_context == 0)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	else if (g_context == 1)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		g_context = 0;
// 	}
// 	else if (g_context == 2)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		ioctl(STDIN_FILENO, TIOCSTI, (char *)"\n");
// 		exit(1);
// 	}
// 	aux_signals(signal);
// }

// void	init_signals(void)
// {
// 	g_context = 0;
// 	signal(SIGINT, handle_signals);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_minishell.trigered = 1;
		if (g_minishell.context == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else if (g_minishell.context == 1)
		{
			write(STDOUT_FILENO, "\n", 1);
		}
		else if (g_minishell.context == 2)
		{
			write(STDOUT_FILENO, "\n", 1);
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
		}
	}
}

void	init_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

int	exec_builtin(t_shell *shell, t_command *command)
{
	char	*name_command;

	name_command = command->argv[0];
	if (!name_command)
		return (0);
	if (ft_strncmp(name_command, "echo", 4) == 0)
		return (ft_echo(command->argv));
	else if (ft_strncmp(name_command, "env", 3) == 0)
		return (ft_env(shell, command->argv));
	else if (ft_strncmp(name_command, "pwd", 3) == 0)
		return (ft_pwd());
	else if (ft_strncmp(name_command, "cd", 2) == 0)
		return (ft_cd(shell, command->argv[1]));
	else if (ft_strcmp(name_command, "export") == 0)
		return (ft_export(shell, command->argv));
	else if (ft_strcmp(name_command, "exit") == 0)
		return (ft_exit(command->argv, command, shell), 0);
	else if (ft_strcmp(name_command, "unset") == 0)
		return (ft_unset(command->argv, shell));
	return (-1);
}

void	join_strings(char *dest, char *s1, char *s2, size_t len1)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len1)
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
}
