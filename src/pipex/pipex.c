/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:45:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/22 11:23:45 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	last_command_exec(t_cmd *cmd)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
		return (ft_error("Fork: "));
	if (pid == 0)
	{
		printf("ultimo comando \n");
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

t_error_code	redir_manager(t_cmd_table *table, int type)
{
	t_error_code	error;
	t_redir			*redir;
	
	error = NO_ERROR;
	if (type == IN_REDIR)
	{
		redir = get_redir_in(table->redirs);
		if (redir != NULL)
			if (manage_redir_in(table, *redir) == -1)
				return (error);
			// error opening fd
	}
	else if (type == OUT_REDIR)
	{
		redir = get_redir_out(table->redirs);
		if (redir != NULL)
			if (manage_redir_out(table, *redir) == -1)
				return (error);
	}
	return error;
}

void	handle_command(t_cmd *cmd, t_cmd_table *table, int *cmd_index, t_error_code *res)
{
		if (cmd->builtin)
			cmd->builtin(table, cmd);
		else if (table->n_pipes > *cmd_index)
		{
			*res = pipex_proccess(cmd, table);
			(*cmd_index)++;
		}
		else
		{
			redir_manager(table, OUT_REDIR);
			last_command_exec(cmd);
		}
}

/* t_error_code	iterate_table(t_cmd_table *table)
{
	// tengo que cambiar el nombre de esta funcion
	t_list	*cmd_list;
	int		cmd_index;
	t_error_code	res;
	t_cmd	*cmd;

	cmd_index = 0;
	cmd_list = table->cmds;
	res = NO_ERROR;
	redir_manager(table, IN_REDIR);
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (is_command(*cmd))
		{
			if (cmd->builtin != NULL)
				cmd->builtin(table, cmd);
			else
			{
				if (table->n_pipes > cmd_index)
				{
					res = pipex_proccess(cmd, table);
					cmd_index++;
				}
				else
				{
					redir_manager(table, OUT_REDIR);
					last_command_exec(cmd);
				}
			}
		}
		if (is_redir(*cmd))
			cmd_list = cmd_list->next;
		cmd_list = cmd_list->next;
	}
	close_red_files(table->red_files);
	while (waitpid(-1, NULL, 0) != -1)
		continue;
	return (res);
} */

t_error_code	execute_cmd_table(t_cmd_table *table)
{
	t_list			*cmd_list;
	int				cmd_index;
	t_error_code	res;
	t_cmd			*cmd;

	cmd_index = 0;
	cmd_list = table->cmds;
	res = NO_ERROR;
	redir_manager(table, IN_REDIR);
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (is_command(*cmd))
			handle_command(cmd, table, &cmd_index, &res);
		if (is_redir(*cmd))
			cmd_list = cmd_list->next;
		cmd_list = cmd_list->next;
	}
	close_red_files(table->red_files);
	while (waitpid(-1, NULL, 0) != -1)
		continue;
	return (res);
}
