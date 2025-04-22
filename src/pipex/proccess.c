/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:05:04 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/22 16:03:14 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_error(char *str)
{
	if (str != NULL)
		perror(str);
	return (EXIT_FAILURE);
}

void	save_original_fd(t_cmd_table *table)
{
	table->std_backup[READ_E] = dup(STDIN_FILENO);
	table->std_backup[WRITE_E] = dup(STDOUT_FILENO);
	if (!table->std_backup[READ_E] || !table->std_backup[WRITE_E])
	{
		table->error_code = DUP_ERROR;
		error_handler(table);
	}
}

void	restore_and_close_fds(t_cmd_table *table)
{
	if ((dup2(table->std_backup[READ_E], STDIN_FILENO) == -1)|| (dup2(table->std_backup[WRITE_E], STDOUT_FILENO) == -1))
	{
		table->error_code = DUP_ERROR;
		error_handler(table);
	}
	// dup2(fd[WRITE_E], STDOUT_FILENO);
	if (close(table->std_backup[READ_E]) || close(table->std_backup[WRITE_E]))
	{
		table->error_code = CLOSE_ERROR;
		error_handler(table);
	}
}


int	pipex_proccess(t_cmd *cmd, t_cmd_table *table)
{
	pid_t	pid;

	printf(PINK "entro en pipex proccess %s \n", RESET_COLOR);
	if (pipe(table->pipe_fd) == -1)
		return (ft_error("pipe: "));
	pid = fork();
	if (pid == -1)
		return (ft_error("Fork: "));
	if (pid == 0)
	{
		close(table->pipe_fd[READ_E]);
		dup2(table->pipe_fd[WRITE_E], STDOUT_FILENO);
		close(table->pipe_fd[WRITE_E]);
		if (cmd->builtin)
			exit(cmd->builtin(table, cmd));
		path_exec(cmd);
	}
	else
	{
		close(table->pipe_fd[WRITE_E]);
		dup2(table->pipe_fd[READ_E], STDIN_FILENO);
		close(table->pipe_fd[READ_E]);
		// waitpid(pid, &status, 0);
	}
	// if (status && WIFEXITED(status))
	// 	return (WEXITSTATUS(status));
	return (NO_ERROR);
} 
