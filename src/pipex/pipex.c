/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:45:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/28 19:06:42 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	last_command_exec(t_cmd *cmd, t_cmd_table *table)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
	{
		table->error_code = FORK_ERROR;
		error_handler(table->error_code);
	}
	if (pid == 0)
	{
		// exit(42);
		printf("ultimo comando \n");
		path_exec(cmd, table);
	}
/* 	else
		waitpid(pid, &status, 0);
	if (status && WIFEXITED(status))
		return (WEXITSTATUS(status)); */
	return (table->error_code);
}

void	redir_manager(t_cmd_table *table, int type)
{
	t_redir			*redir;

	if (type == IN_REDIR)
	{
		redir = get_redir_in(table->redirs);
		if (redir != NULL)
			manage_redir_in(table, *redir);
	}
	else if (type == OUT_REDIR)
	{
		redir = get_redir_out(table->redirs);
		if (redir != NULL)
			manage_redir_out(table, *redir);
	}
}

int	handle_command(t_cmd *cmd, t_cmd_table *table, int *cmd_index)
{
	if (table->n_pipes > *cmd_index)
	{
		table->error_code = pipex_proccess(cmd, table);
		(*cmd_index)++;
	}
	else
	{
		redir_manager(table, OUT_REDIR);
		if (cmd->builtin)
			cmd->builtin(table, cmd);
		else
			table->error_code = last_command_exec(cmd, table);
	}
	return (table->error_code);
}

int	execute_cmd_table(t_cmd_table *table)
{
	t_list			*cmd_list;
	int				cmd_index;
	t_cmd			*cmd;
	int				status;

	cmd_index = 0;
	status = 0;
	cmd_list = table->cmds;
	redir_manager(table, IN_REDIR);
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		// printf("current cmd --> %s \n", ((t_tok *)cmd->tokens)->value );
		if (is_command(*cmd))
			table->error_code = handle_command(cmd, table, &cmd_index);
		if (is_redir(*cmd))
			cmd_list = cmd_list->next;
		cmd_list = cmd_list->next;
	}
	close_red_files(table->red_files);
	while (waitpid(-1, &status, 0) != -1)
		continue ;
	if (WIFSIGNALED(status))
		table->error_code = 128 + WTERMSIG(status);
	else
		table->error_code = WEXITSTATUS(status);
	return (table->error_code);
}
