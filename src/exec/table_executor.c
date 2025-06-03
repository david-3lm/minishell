/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:45:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/06/03 21:13:37 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_command(t_cmd *cmd, t_cmd_table *table)
{
	if (cmd->builtin)
		cmd->builtin(table, cmd);
	else if (cmd->tokens)
		(table)->error_code = command_exec(cmd, table);
	return ((table)->error_code);
}

int	ft_wait_table(void)
{
	int	status;
	int	code;

	status = 0;
	while (waitpid(-1, &status, 0) != -1)
		continue ;
	if (WIFSIGNALED(status))
		code = 128 + WTERMSIG(status);
	else
		code = WEXITSTATUS(status);
	return (code);
}

/* static	int	exec_cmd_list(t_list *cmd_list, t_cmd_table *table, int i)
{
	t_cmd	*cmd;

	if (!cmd_list)
		return (NO_ERROR);
	save_original_fd((table));
	cmd = (t_cmd *)cmd_list->content;
	set_redir_pipes(cmd->redirs, table, i);
	if (is_kntxesi(*cmd))
	{
		(table)->error_code = execute_kntxesi(table);
		return (table->error_code);
	}
	// if (fill_redirs(cmd, table) != NO_ERROR)
	// 	return (table->error_code);
	// if (ft_check_redirs(table, cmd))
		(table)->error_code = handle_command(cmd, table, &i);
	// else
		// i++;
	if (cmd_list)
		cmd_list = cmd_list->next;
	// close_red_fd(table->red_fd);
	close_red_fd(table->pipe_fd);
	restore_and_close_fds((table));
	return (exec_cmd_list(cmd_list, table, i));
} */
static int	exec_cmd_list(t_list *cmd_list, t_cmd_table *table, int i)
{
	t_cmd	*cmd;
	int		n_cmds;

	n_cmds = table->n_cmd;
	if (!cmd_list)
		return (NO_ERROR);
	save_original_fd((table));
	cmd = (t_cmd *)cmd_list->content;
	set_redir_pipes(cmd->redirs, table, i);
	if (is_kntxesi(*cmd))
	{
		(table)->error_code = execute_kntxesi(table);
		return (table->error_code);
	}
	if (ft_check_redirs(cmd))
		handle_command(cmd, table);
	else
		i++;
	if (cmd_list)
		cmd_list = cmd_list->next;
	restore_and_close_fds((table));
	return (exec_cmd_list(cmd_list, table, i));
}

int	table_executor(t_cmd_table *table)
{
	t_list	*cmd_list;
	int		cmd_index;
	int		code;

	cmd_index = 0;
	cmd_list = (table)->cmds;
	table->n_cmd = ft_lstsize(cmd_list);
	ft_init_pipes(table);
	exec_cmd_list(cmd_list, table, cmd_index);
	code = ft_wait_table();
	if (table->error_code == NO_ERROR)
		table->error_code = code;
	close_all_pipes(table);
	return ((table)->error_code);
}
