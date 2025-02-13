/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:05:04 by cde-migu          #+#    #+#             */
/*   Updated: 2025/02/13 12:02:04 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_error(char *str)
{
	if (str != NULL)
		perror(str);
	return (EXIT_FAILURE);
}

/* int	old_pipex_proccess(char *argv)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		return (ft_error("pipe: "));
	pid = fork();
	if (pid == -1)
		return (ft_error("Fork: "));
	if (pid == 0)
	{
		close(fd[READ_E]);
		dup2(fd[WRITE_E], STDOUT_FILENO);
		path_exec(argv);
	}
	else
	{
		close(fd[WRITE_E]);
		dup2(fd[READ_E], STDIN_FILENO);
		waitpid(pid, &status, 0);
	}
	if (status && WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
} */

void	save_original_fd(int fd[2])
{
	dup2(fd[READ_E], STDIN_FILENO);
	dup2(fd[WRITE_E], STDOUT_FILENO);
}

void	restore_fds(int fd[2])
{
	dup2(STDIN_FILENO, fd[READ_E]);
	dup2(STDOUT_FILENO, fd[WRITE_E]);
}

int	pipex_proccess(t_cmd *cmd, t_cmd_table *table)
{
	pid_t	pid;

	printf("entro en pipex proccess \n");
	if (pipe(table->pipe_fd) == -1)
		return (ft_error("pipe: "));
	pid = fork();
	if (pid == -1)
		return (ft_error("Fork: "));
	if (pid == 0)
	{
		close(table->pipe_fd[READ_E]);
		dup2(table->pipe_fd[WRITE_E], STDOUT_FILENO);
		path_exec(cmd);
	}
	else
	{
		close(table->pipe_fd[WRITE_E]);
		dup2(table->pipe_fd[READ_E], STDIN_FILENO);
		// waitpid(pid, &status, 0);
	}
	// if (status && WIFEXITED(status))
	// 	return (WEXITSTATUS(status));
	return (NO_ERROR);
}
