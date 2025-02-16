/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/02/16 11:39:59 by cde-migu         ###   ########.fr       */
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
	// ESTE EXECUTOR FUNCIONA CON UN SOLO COMANDO
	t_list	*cmd_list;
	int		cmd_index;
	t_error_code	res;
	// t_error_code	last_res;
	t_cmd	*cmd;

	cmd_index = 0;
	cmd_list = table->cmds;
	res = NO_ERROR;
	// last_res = NO_ERROR;
	// if (count_redirs()
	save_original_fd(table->std_backup);
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (is_command(*cmd))
		{
			printf("index --> %d, n_pipes --> %d \n", cmd_index, table->n_pipes);
			if (table->n_pipes > cmd_index)
			{
				res = pipex_proccess(cmd, table);
				cmd_index++;
			}
			else
				last_command_exec(cmd);
		}
		cmd_list = cmd_list->next;
	}
	restore_fds(table->std_backup);
	while (waitpid(-1, NULL, 0) != -1)
		continue;
	//DEFINE EXIT CODE WITH WEXITSTATUS
	
	// if (last_res != NO_ERROR && res != last_res)
	// 	res = last_res;
	return (res);
}
