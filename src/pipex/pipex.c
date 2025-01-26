/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:45:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/01/14 19:37:22 by cde-migu         ###   ########.fr       */
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

t_tok_type	get_next_type(t_list *cmd)
{
	t_list *aux;
	t_tok	*token;
	
	aux = cmd->next;
	token = (t_tok *)aux->content;
	return (token->type);
}

int	pipex(t_cmd_table *table)
{
	// leer la command table, identificar los cmd y los pipes
	// si es pipe, hacer ese pipe y pasar al siguiente 
	// el numero de pipes
	
}
