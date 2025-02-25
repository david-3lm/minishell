/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/02/25 11:59:47 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void prueba_test(void)
{
	ft_printf("hola");
}

int	last_command_exec(t_cmd *cmd)
{
	pid_t	pid;
	// int		status;

	pid = fork();
	if (pid == -1)
		return (ft_error("Fork: "));
	if (pid == 0)
	{
		printf("he entrado a hacer el ultimo comando \n");
		path_exec(cmd);
	}
/* 	else
		waitpid(pid, &status, 0);
	if (status && WIFEXITED(status))
		return (WEXITSTATUS(status)); */
	return (NO_ERROR);
}



t_error_code	executor(t_cmd_table *table)
{
	t_error_code	res;
	res = pipex(table);
	return (res);
}
