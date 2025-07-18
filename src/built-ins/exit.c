/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:59 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/07 13:17:22 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/structs.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static void	free_exit(t_command *cmd, t_shell *data, long long exit_code)
{
	free_command(cmd);
	free_minishell(data);
	if (exit_code < 0)
		exit(156);
	else
		exit(exit_code);
}

long long	ft_atoll(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	is_numeric(const char *str)
{
	if (!str)
		return (0);
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (!isdigit((unsigned char)*str))
		return (0);
	while (*str)
	{
		if (!isdigit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

int	ms_check_exit_arg(char *arg, t_shell *shell)
{
	long long	exit_code;

	exit_code = 0;
	if (arg && !is_numeric(arg))
	{
		printf("minishell: exit: %s: numeric argument required\n", arg);
		shell->exit = 255;
		return (1);
	}
	if (arg)
		exit_code = ft_atoll(arg);
	shell->exit = (unsigned char)exit_code;
	return (0);
}

void	ft_exit(char **arg, t_command *cmd, t_shell *shell)
{
	if (arg && arg[0])
	{
		if (arg[1] && ms_check_exit_arg(arg[1], shell) == 0 && arg[2])
		{
			printf("minishell: exit: too many arguments\n");
			shell->exit = 1;
			return ;
		}
	}
	printf("exit\n");
	free_exit(cmd, shell, 2);
	exit(shell->exit);
}
