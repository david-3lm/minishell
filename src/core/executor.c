/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/30 10:35:35 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	executor(t_cmd_table *table)
{
	save_original_fd(table);
	table->error_code = execute_cmd_table(table);
	restore_and_close_fds(table);
	//TODO: borrar la siguiente linea
	printf("error code executor --> %d \n", table->error_code);
	return (table->error_code);
}
