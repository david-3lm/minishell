/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:45:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/21 15:18:06 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	last_command_exec(t_cmd *cmd, t_cmd_table *table)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		check_error(pid, CHECK_FORK, table);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		path_exec(cmd, table);
	}
	return (table->error_code);
}

int	handle_command(t_cmd *cmd, t_cmd_table *table, int *cmd_index)
{
	if ((table->n_cmd - 1) > *cmd_index)
	{
		(table)->error_code = pipex_proccess(cmd, table);
		(*cmd_index)++;
	}
	else
	{
		// if (cmd->builtin)
		// 	cmd->builtin(table, cmd);
		// else
			(table)->error_code = last_command_exec(cmd, table);
	}
	return ((table)->error_code);
}

int	ft_wait_table(t_cmd_table *table)
{
	int				status;

	status = 0;
	while (waitpid(-1, &status, 0) != -1)
		continue ;
	if (WIFSIGNALED(status))
		(table)->error_code = 128 + WTERMSIG(status);
	else
		(table)->error_code = WEXITSTATUS(status);
	return ((table)->error_code);
}

static	int	exec_cmd_list(t_list *cmd_list, t_cmd_table *table, int i)
{
	t_cmd	*cmd;

	if (!cmd_list)
		return (NO_ERROR);

	cmd = (t_cmd *)cmd_list->content;
	// if (is_kntxesi(*cmd)) //mirar si es necesario
	// 	(table)->error_code = execute_kntxesi(table);
	fill_redirs(cmd, table);
	redir_dup(table);
	(table)->error_code = handle_command(cmd, table, &i);
	// if (is_redir(*cmd))
	// 	cmd_list = cmd_list->next;
	if (cmd_list)
		cmd_list = cmd_list->next;
	close_red_fd((table)->red_fd);
	return (exec_cmd_list(cmd_list, table, i));
}

int	execute_cmd_table(t_cmd_table *table)
{
	t_list	*cmd_list;
	int		cmd_index;	

	cmd_index = 0;
	cmd_list = (table)->cmds;
	save_original_fd((table));
	table->n_cmd = ft_lstsize(cmd_list);
	exec_cmd_list(cmd_list, table, cmd_index);
	(table)->error_code = ft_wait_table(table);
	restore_and_close_fds((table));
	return ((table)->error_code);
}
