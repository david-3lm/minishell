/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:05:04 by cde-migu          #+#    #+#             */
/*   Updated: 2025/06/03 21:11:29 by cde-migu         ###   ########.fr       */
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
	// check_error(cl, CHECK_CLOSE, table);
	cl = close(table->std_backup[WRITE_E]);
	// check_error(cl, CHECK_CLOSE, table);
}

int	try_fullpath(char *path, char **full_cmd, char *const *envp, t_cmd_table *table)
// int	try_fullpath(char *path, char **full_cmd, \
// 				char *const *envp, t_cmd_table *table)
{
	errno = 0;
	if (access(path, F_OK) == 0)
	{
		execve(path, full_cmd, envp);
		ft_wrong_access_error(table, full_cmd[0], PERMISSION_ERROR);
		return (table->error_code);
	}
	return (NO_ERROR);
}

int	last_command_exec(t_cmd *cmd, t_cmd_table *table)
{
	pid_t	pid;
	t_list	*new_pid;

	pid = fork();
	if (pid == -1)
		check_error(pid, CHECK_FORK, table);
	if (pid == 0)
	{
		close_red_fd(table->std_backup);
		signal(SIGQUIT, SIG_DFL);
		path_exec(cmd, table);
	}
	new_pid = ft_lstnew(&pid);
	ft_lstadd_back(&table->pids, new_pid);
	return (table->error_code);
}

int	command_exec(t_cmd *cmd, t_cmd_table *table, int i)
{
	pid_t	pid;
	t_list	*new_pid;

	change_token(*(table->envv), ft_create_env \
				("_", (char *)ft_lstlast(cmd->tokens)->content));
	pid = fork();
	if (pid == -1)
		check_error(pid, CHECK_FORK, table);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close(table->pipes[i][READ_E]);
		dup2(table->pipes[i][WRITE_E], STDOUT_FILENO);
		close(table->pipes[i][WRITE_E]);
		// close_all_pipes(table);
		path_exec(cmd, table);

	}
	else
	{
		close(table->pipes[i][WRITE_E]);
		dup2((table)->pipes[i][READ_E], STDIN_FILENO);
		close(table->pipes[i][READ_E]);
		close_all_pipes(table);
	}
	new_pid = ft_lstnew(&pid);
	ft_lstadd_back(&table->pids, new_pid);
	return (table->error_code);
}
