/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:05:04 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/08 13:06:28 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		if (cmd->builtin)
			exit(cmd->builtin(table, cmd));
		path_exec(cmd, table);
	}
	else
	{
		close((table)->pipe_fd[WRITE_E]);
		value = dup2((table)->pipe_fd[READ_E], STDIN_FILENO);
		check_error(value, CHECK_DUP, table);
		close((table)->pipe_fd[READ_E]);
	}
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		perror("Signal");
	return ((table)->error_code);
}

int	try_fullpath(char *path, char **full_cmd, char *const *envp)
{
	if (access(path, X_OK) == 0)
		execve(path, full_cmd, envp);
	return (-1);
}
