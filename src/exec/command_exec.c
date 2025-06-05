/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:49:19 by cde-migu          #+#    #+#             */
/*   Updated: 2025/06/05 11:49:58 by cde-migu         ###   ########.fr       */
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
	cl = close(table->std_backup[WRITE_E]);
}

int	try_fullpath(char *path, char **full_cmd, \
				char *const *envp, t_cmd_table *table)
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

int	last_command_exec(t_cmd *cmd, t_cmd_table *table, int i)
{
	pid_t	pid;
	t_list	*new_pid;

	pid = fork();
	if (pid == -1)
		check_error(pid, CHECK_FORK, table);
	if (pid == 0)
	{
		set_redir_pipes(cmd->redirs, table, i);
		close_unused_pipes(table, i);
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
		set_redir_pipes(cmd->redirs, table, i);
		close_unused_pipes(table, i);
		close_red_fd(table->std_backup);
		if (cmd->builtin)
			exit(cmd->builtin(table, cmd));
		path_exec(cmd, table);
	}
	else
		close(table->pipes[i][WRITE_E]);
	new_pid = ft_lstnew(&pid);
	ft_lstadd_back(&table->pids, new_pid);
	return (table->error_code);
}
