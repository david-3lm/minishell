/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:44:08 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/30 16:48:17 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redir_dup(t_cmd_table *table)
{
	int	err;

	if (table->red_fd[READ_E] != 0)
	{
		err = dup2(table->red_fd[READ_E], STDIN_FILENO);
		check_error(err, CHECK_DUP, table);
		err = close(table->red_fd[READ_E]);
		check_error(err, CHECK_CLOSE, table);
		table->red_fd[READ_E] = 0;
	}
	if (table->red_fd[WRITE_E] != 0)
	{
		err = dup2(table->red_fd[WRITE_E], STDOUT_FILENO);
		check_error(err, CHECK_DUP, table);
		err = close(table->red_fd[WRITE_E]);
		check_error(err, CHECK_CLOSE, table);
		table->red_fd[WRITE_E] = 0;
	}
}

void	close_red_fd(int files[2])
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (files[i] != 0)
			close(files[i]);
		i++;
	}
}

bool	ft_check_redirs(t_cmd_table *table, t_cmd *cmd)
{
	if ((ft_strcmp((char *)cmd->tokens->content, "")) && \
		(table->red_fd[READ_E] == -1 || table->red_fd[WRITE_E] == -1))
		return (false);
	return (true);
}
