/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:45:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/06/05 11:50:44 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_command(t_cmd *cmd, t_cmd_table *table, int *cmd_index)
{
	if ((table->n_cmd - 1) > *cmd_index)
	{
		(table)->error_code = command_exec(cmd, table, *cmd_index);
		(*cmd_index)++;
	}
	else
	{
		if (cmd->builtin)
			cmd->builtin(table, cmd);
		else if (cmd->tokens)
			(table)->error_code = last_command_exec(cmd, table, *cmd_index);
	}
	return ((table)->error_code);
}

int	ft_wait_table(t_list **pids)
{
	int		code;
	int		status;
	long	pid;

	while (*pids)
	{
		pid = (long)(*pids)->content;
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status))
			code = 128 + WTERMSIG(status);
		else
			code = WEXITSTATUS(status);
		ft_lstdel_first(pids, ft_lstdel_safe);
	}
	return (code);
}

static int	exec_cmd_list(t_list *cmd_list, t_cmd_table *table, int i)
{
	t_cmd	*cmd;
	int		n_cmds;

	n_cmds = table->n_cmd;
	if (!cmd_list)
		return (NO_ERROR);
	cmd = (t_cmd *)cmd_list->content;
	if (is_kntxesi(*cmd))
	{
		(table)->error_code = execute_kntxesi(table);
		return (table->error_code);
	}
	if (ft_check_redirs(cmd))
		handle_command(cmd, table, &i);
	else
		i++;
	if (cmd_list)
		cmd_list = cmd_list->next;
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
	save_original_fd((table));
	exec_cmd_list(cmd_list, table, cmd_index);
	restore_and_close_fds((table));
	close_all_pipes(table);
	code = ft_wait_table(&table->pids);
	if (table->error_code == NO_ERROR)
		table->error_code = code;
	return ((table)->error_code);
}
