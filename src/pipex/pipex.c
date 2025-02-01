/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:45:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/02/01 13:40:29 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	old_pipex(char **argv, int argc)
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
}

int	old_last_child(char **argv, int argc)
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
}

bool	is_pipe_ok(t_list *current)
{
	t_list *current;
	t_list *next;
	t_list *second_next;

	next = current->next;
	second_next = next->next;
	if (is_command(current) && (get_token_type(next) == PIPE) && (get_token_type(second_next) == COMMAND))
		return (true);
	else
		return (false);
}

int	last_child(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (ft_error("Fork: "));
	if (pid == 0)
		path_exec(cmd);
	else
		waitpid(pid, &status, 0);
	if (status && WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	pipex(t_cmd_table *table)
{
	// leer la command table, identificar los cmd y los pipes
	// si es pipe, hacer ese pipe y pasar al siguiente 
	// el numero de pipes
	t_list	*cmd_list;
	t_cmd	*current_cmd;
	// int		files[2];
	int		i;
	
	i = 0;
	cmd_list = table->cmds;
	// pipe(files);
	while (i < table->n_pipes)
	{
		current_cmd = (t_cmd *)cmd_list->content;
		pipex_proccess(current_cmd);
		cmd_list = cmd_list->next;
		i++;
	}
	last_child(current_cmd);
}
