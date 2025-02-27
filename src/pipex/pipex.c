/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:45:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/02/27 20:39:01 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* int	old_pipex(char **argv, int argc)
{
	int	i;
	int	output;
	int	last_output;

	i = 0;
	output = 0;
	while (i < argc - 1)
	{
		output = old_pipex_proccess(argv[i]);
		i++;
	}
	last_output = old_last_child(argv, argc);
	if (last_output && output != last_output)
		output = last_output;
	return (output);
} */

/* int	old_last_child(char **argv, int argc)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (ft_error("Fork: "));
	if (pid == 0)
	{
		dup2(files->outfile, STDOUT_FILENO);
		path_exec(argv[argc - 2]);
	}
	else
		waitpid(pid, &status, 0);
	if (status && WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
} */

t_error_code	pipex(t_cmd_table *table)
{
	t_list	*cmd_list;
	int		cmd_index;
	t_error_code	res;
	// t_error_code	last_res;
	t_cmd	*cmd;
	t_redir	*redir;

	cmd_index = 0;
	cmd_list = table->cmds;
	res = NO_ERROR;
	// last_res = NO_ERROR;
	save_original_fd(table->std_backup);
	redir = get_redir_in(table->redirs);
	if (redir != NULL)
		manage_redir_in(table, *redir);
	redir = NULL;
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
			{
				redir = get_redir_out(table->redirs);
				if (redir != NULL)
					manage_redir_out(table, *redir);
				last_command_exec(cmd);
			}
		}
		if (is_redir(*cmd))
			cmd_list = cmd_list->next;
		cmd_list = cmd_list->next;
	}
	restore_fds(table->std_backup);
	close_red_files(table->red_files);
	while (waitpid(-1, NULL, 0) != -1)
		continue;
	//DEFINE EXIT CODE WITH WEXITSTATUS
	
	// if (last_res != NO_ERROR && res != last_res)
	// 	res = last_res;
	return (res);
}
