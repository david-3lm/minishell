/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_and_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:52:37 by cde-migu          #+#    #+#             */
/*   Updated: 2025/06/03 21:32:10 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_init_pipes(t_cmd_table *table)
{
	int	i;

	i = 0;
	if (table->n_cmd == 1)
		table->pipes = NULL;
	table->pipes = ft_calloc(table->n_cmd, sizeof(int *));
	while (i < table->n_cmd - 1)
	{
		table->pipes[i] = ft_calloc(2, sizeof(int));
		if (!table->pipes[i])
			check_error(CHECK_VALUE, CHECK_MEM, table);
		if (pipe(table->pipes[i]) == CHECK_VALUE)
			check_error(CHECK_VALUE, CHECK_PIPE, table);
		i++;
	}
	return (table->error_code);
}

void	set_redir_pipes(t_list *redirs, t_cmd_table *table, int index)
{
	int	**pipes;
	int	n_cmds;
	int	err_value;

	n_cmds = table->n_cmd;
	pipes = table->pipes;
	err_value = NO_ERROR;
	if (open_all_files(redirs, table) != NO_ERROR)
	{
		table->error_code = UNKNOWN_ERROR;
		return ;
	}
	if (!is_redirs(redirs, RD_SIN) && index != 0)
		err_value = dup2(pipes[index - 1][READ_E], STDIN_FILENO);
	if (!is_redirs(redirs, RD_SOUT) && !is_redirs(redirs, RD_SOUT2) \
		&& index != n_cmds - 1)
		err_value = dup2(pipes[index][WRITE_E], STDOUT_FILENO);
	check_error(err_value, DUP_ERROR, table);
}

void	close_all_pipes(t_cmd_table *table)
{
	int	i;
	int	nb_pipes;

	i = 0;
	nb_pipes = table->n_cmd - 1;
	while (i < nb_pipes)
	{
		close(table->pipes[i][0]);
		close(table->pipes[i][1]);
		i++;
	}
}

void	free_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
