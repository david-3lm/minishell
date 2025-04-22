/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/21 17:40:09 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void debug_pink(char *str)
{
	printf(PINK "%s" RESET_COLOR, str);
}

t_error_code	executor(t_cmd_table *table)
{
	t_error_code	res;
	
	res = NO_ERROR;
	if (!table || !table->cmds)
		return res;
	save_original_fd(table->std_backup);
	res = execute_cmd_table(table);
	restore_and_close_fds(table->std_backup);
	return (res);
}
