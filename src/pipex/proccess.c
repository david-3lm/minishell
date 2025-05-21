/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:05:04 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/21 12:28:35 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <errno.h>

void	save_original_fd(t_cmd_table *table)
{
	table->std_backup[READ_E] = dup(STDIN_FILENO);
	check_error(table->std_backup[READ_E], CHECK_DUP, table);
	table->std_backup[WRITE_E] = dup(STDOUT_FILENO);
	check_error(table->std_backup[WRITE_E], CHECK_DUP, table);
}

void	restore_and_close_fds(t_cmd_table *table)
{
	int	cl;

	dup2(table->std_backup[READ_E], STDIN_FILENO);
	check_error(table->std_backup[READ_E], CHECK_DUP, table);
	dup2(table->std_backup[WRITE_E], STDOUT_FILENO);
	check_error(table->std_backup[READ_E], CHECK_DUP, table);
	cl = close(table->std_backup[READ_E]);
	check_error(cl, CHECK_CLOSE, table);
	cl = close(table->std_backup[WRITE_E]);
	check_error(cl, CHECK_CLOSE, table);
}

int	pipex_proccess(t_cmd *cmd, t_cmd_table *table)
{
	pid_t	pid;
	int		value;

	check_error(pipe((table)->pipe_fd), CHECK_PIPE, table);
	pid = fork();
	check_error(pid, CHECK_FORK, table);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close((table)->pipe_fd[READ_E]);
		value = dup2((table)->pipe_fd[WRITE_E], STDOUT_FILENO);
		check_error(value, CHECK_DUP, table);
		close((table)->pipe_fd[WRITE_E]);
		// if (cmd->builtin)
		// 	exit(cmd->builtin(table, cmd));
		path_exec(cmd, table);
	}
	else
	{
		close((table)->pipe_fd[WRITE_E]);
		value = dup2((table)->pipe_fd[READ_E], STDIN_FILENO);
		check_error(value, CHECK_DUP, table);
		close((table)->pipe_fd[READ_E]);
	}
	return ((table)->error_code);
}

int	try_fullpath(char *path, char **full_cmd, \
				char *const *envp, t_cmd_table *table)
{
	errno = 0;
	if (access(path, F_OK) == 0)
	{
		printf("hola \n");
		execve(path, full_cmd, envp);
		ft_wrong_access_error(table, full_cmd[0], PERMISSION_ERROR);
		return (table->error_code);
	}
	return (NO_ERROR);
}
