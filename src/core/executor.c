/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/02/01 16:33:51 by cde-migu         ###   ########.fr       */
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
	int		status;

	pid = fork();
	printf("HOLA \n");
	if (pid == -1)
		return (ft_error("Fork: "));
	if (pid == 0)
		path_exec(cmd);
	else
		waitpid(pid, &status, 0);
	if (status && WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (NO_ERROR);
}

t_error_code	pipe_manager(t_cmd_table *table)
{
	t_list	*cmd_list;
	int		cmd_index;
	t_error_code	res;
	t_error_code	last_res;
	t_cmd	*current_cmd;

	cmd_index = 0;
	cmd_list = table->cmds;
	res = NO_ERROR;
	while (cmd_list && cmd_index < table->n_pipes)
	{
		current_cmd = (t_cmd *)cmd_list->content;
		res = pipex_proccess(current_cmd);
		cmd_list = cmd_list->next;
		cmd_index++;
	}
	last_res = last_command_exec(current_cmd);
	if (last_res != NO_ERROR && res != last_res)
		res = last_res;
	return (res);
}

/* t_error_code	executor(t_cmd_table *table)
{
	
	// (void )table;
	t_error_code	res;

	if (table && table->cmds)
		res = pipe_manager(table);
	else
		res = UNKNOWN_ERROR;
	return (res);
} */
 t_error_code	executor(t_cmd_table *table)
{
// ESTE EXECUTOR FUNCIONA CON UN SOLO COMANDO
	t_list	*cmd_list;
	int		cmd_index;
	t_error_code	res;
	t_cmd	*cmd;

	cmd_index = 0;
	cmd_list = table->cmds;
	res = NO_ERROR;
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		/* if (is_command(*cmd))
		{
			res = last_command_exec(cmd);
		} */
		if (is_command(*cmd))
		{
			if (table->n_pipes > cmd_index)
			{
				res = pipex_proccess(cmd);
				cmd_list = cmd_list->next;
				cmd_index++;
			}
			else
			{
				res = last_command_exec(cmd);
				cmd_list = cmd_list->next;
				cmd_index++;
			}
		}
		else
		{
			cmd_list = cmd_list->next;
		}
	}
	(void )table;
	return (res);
}
