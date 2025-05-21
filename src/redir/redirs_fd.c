/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:44:08 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/21 15:13:36 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redir_dup(t_cmd_table *table)
{
	int	err;

	// printf("redir dup \t FDS ABIERTOS table-> red[READE] == %i, \t table-> red[WRITE] == %i \n ",table->red_fd[READ_E], table->red_fd[WRITE_E] );
	if (table->red_fd[READ_E] != 0)
	{
		err = dup2(table->red_fd[READ_E], STDIN_FILENO);
		check_error(err, CHECK_DUP, table);
		// printf(" REDIR DUP voy a cerrar fd ---> %i \n", table->red_fd[READ_E]);
		err = close(table->red_fd[READ_E]);
		check_error(err, CHECK_CLOSE, table);
		table->red_fd[READ_E] = 0;
	}
	if (table->red_fd[WRITE_E] != 0)
	{
		err = dup2(table->red_fd[WRITE_E], STDOUT_FILENO);
		// ft_putstr_fd("error en redir dup ---> ", 2);
		// ft_putendl_fd(ft_itoa(err), 2);
		// ft_putendl_fd("holaaaaaa pito", 2);
		check_error(err, CHECK_DUP, table);
		// ft_putendl_fd("REDIR DUP voy a cerrar fd --- \n", 2);
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
		{
		printf(" DENTRO DE CLOSE RED FD ---- voy a cerrar fd ---> %i \n", i);
			
			close(files[i]);
		}
		i++;
	}
}
