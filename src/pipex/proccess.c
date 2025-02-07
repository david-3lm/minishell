/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:05:04 by cde-migu          #+#    #+#             */
/*   Updated: 2025/02/07 18:45:54 by cde-migu         ###   ########.fr       */
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

int	pipex_proccess(t_cmd *cmd)
{
	pid_t	pid;
	int		fd[2];
	// int		status;
	
	// status = 0;
	printf("entro en pipex proccess \n");
	if (pipe(fd) == -1)
		return (ft_error("pipe: "));
	pid = fork();
	if (pid == -1)
		return (ft_error("Fork: "));
	if (pid == 0)
	{
		close(fd[READ_E]);
		dup2(fd[WRITE_E], STDOUT_FILENO);
		close(fd[WRITE_E]);
		path_exec(cmd);
	}
	else
	{
		close(fd[WRITE_E]);
		dup2(fd[READ_E], STDIN_FILENO);
		close(fd[READ_E]);
		// waitpid(pid, &status, 0);
	}
	// if (status && WIFEXITED(status))
	// 	return (WEXITSTATUS(status));
	return (NO_ERROR);
}
