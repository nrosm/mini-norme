/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:33:54 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/05 17:50:32 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

char	*filter_path(t_env *envp, char *key)
{
	size_t	length;

	if (!envp || !key)
		return (NULL);
	length = ft_strlen(key);
	while (envp)
	{
		if (envp->key && ft_strncmp(envp->key, key, length) == 0)
			return (ft_strdup(envp->value));
		envp = envp->next;
	}
	return (NULL);
}

static void	child_process_exec(t_shell *shell, t_command *cmd, t_env *envp)
{
	char	*full_path;
	char	**env_array;

	if (apply_redirs(cmd) == -1)
		exit(1);
	if (is_command(cmd->argv[0]))
		exit(exec_builtin(shell, cmd));
	full_path = find_executable(cmd->argv[0], envp);
	if (!full_path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
	env_array = env_list_to_array(envp);
	execve(full_path, cmd->argv, env_array);
	perror("execve");
	ft_free_array(env_array);
	free(full_path);
	exit(126);
}

int	only_execute(t_shell *shell, t_command *command, t_env *envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	else if (pid == 0)
		child_process_exec(shell, command, envp);
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (1);
}

int	executor(t_shell *shell)
{
	t_command	*command;
	int			save_stdin;
	int			save_stdout;

	if (!shell->commands)
		return (1);
	if (!shell->commands->next)
	{
		command = shell->commands;
		if (is_command(command->argv[0]))
		{
			save_stdin = dup(STDIN_FILENO);
			save_stdout = dup(STDOUT_FILENO);
			apply_redirs(command);
			exec_builtin(shell, command);
			dup2(save_stdin, STDIN_FILENO);
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdin);
			close(save_stdout);
			return (0);
		}
		else
			return (only_execute(shell, command, shell->env));
	}
	return (executor_with_pipes(shell));
}
