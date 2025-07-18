/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:33:37 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/05 12:45:08 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error(void)
{
	perror("error");
	exit(EXIT_FAILURE);
}

int	apply_redirs(t_command *command)
{
	if (command->heredoc != -1)
	{
		if (dup2(command->heredoc, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(command->heredoc);
			return (-1);
		}
		close(command->heredoc);
	}
	if (command->infile && redirect_input(command->infile) == -1)
		return (-1);
	if (command->outfile && redirect_output(command->outfile) == -1)
		return (-1);
	if (command->append && redirect_output_append(command->append) == -1)
		return (-1);
	return (0);
}

int	count_commands(t_command *commands)
{
	int	count;

	count = 0;
	while (commands)
	{
		count++;
		commands = commands->next;
	}
	return (count);
}

char	*find_executable(char *command, t_env *envp)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path_env = filter_path(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, command, 1);
		if (access(full_path, X_OK) == 0)
			return (ft_free_array(paths), full_path);
		free(full_path);
		i++;
	}
	return (ft_free_array(paths), NULL);
}

int	**create_pipes(int cmd_count)
{
	int	**pipes;
	int	i;
	int	j;

	i = 0;
	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		return (NULL);
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			j = 0;
			while (j < i)
			{
				free(pipes[j]);
				j++;
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
