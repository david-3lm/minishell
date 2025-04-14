/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:45:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/14 16:10:07 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	last_command_exec(t_cmd *cmd)
{
	pid_t	pid;
	// int		status;

	// if (is_builtin(cmd) == true)
	// 	check_built_ins(table, cmd);
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
t_error_code	run_pipex(t_cmd_table *table, t_cmd *cmd, int cmd_index)
{
	t_error_code	res;

	printf("index --> %d, n_pipes --> %d \n", cmd_index, table->n_pipes);
	if (table->n_pipes > cmd_index)
	{
		res = pipex_proccess(cmd, table);
		cmd_index++;
	}
	else
		last_command_exec(cmd);
	return (res);
}

t_error_code	iterate_table(t_cmd_table *table)
{
	// tengo que cambiar el nombre de esta funcion
	t_list	*cmd_list;
	int		cmd_index;
	t_error_code	res;
	t_cmd	*cmd;
	t_redir	*redir;

	cmd_index = 0;
	cmd_list = table->cmds;
	res = NO_ERROR;
	// last_res = NO_ERROR;
	save_original_fd(table->std_backup);
	redir = get_redir_in(table->redirs);
	// esta parte de las redirecciones se puede refactorizar, 
	// todo en una funcion que mire si hay in/heredoc y lo gestione ahi en su sitio
	if (redir != NULL)
	{
		if (manage_redir_in(table, *redir) == -1)
			return (NO_ERROR);
	}
	redir = NULL;
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (is_command(*cmd))
		{
			printf( PINK "index --> %d, n_pipes --> %d %s\n", cmd_index, table->n_pipes, RESET_COLOR);
			if (table->n_pipes > cmd_index)
			{
				res = pipex_proccess(cmd, table);
				cmd_index++;
			}
			else
			{
				redir = get_redir_out(table->redirs);
				if (redir != NULL)
					if (manage_redir_out(table, *redir) == -1)
						return (NO_ERROR);
				last_command_exec(cmd);
			}
		}
		if (is_redir(*cmd))
			cmd_list = cmd_list->next;
		cmd_list = cmd_list->next;
	}
	close_red_files(table->red_files);
	while (waitpid(-1, NULL, 0) != -1)
		continue;
	restore_fds(table->std_backup);
	return (res);
}
