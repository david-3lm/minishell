/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:45:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/01/26 16:52:47 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipex(char **argv, int argc)
{
	int	i;
	int	output;
	int	last_output;

	i = 0;
	output = 0;
	while (i < argc - 1)
	{
		output = pipex_proccess(argv[i]);
		i++;
	}
	last_output = last_child(argv, argc);
	if (last_output && output != last_output)
		output = last_output;
	return (output);
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

int	pipex(t_cmd_table *table)
{
	// leer la command table, identificar los cmd y los pipes
	// si es pipe, hacer ese pipe y pasar al siguiente 
	// el numero de pipes
	t_list	*current_cmd;
	int		files[2];
	int		i;
	
	command_list = table->cmds;
	pipe(files);
	while (i < n_cmd)
	{
		if (is_pipe_ok(current_cmd))
			
	}
}
