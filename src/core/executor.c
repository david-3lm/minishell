/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/22 18:40:46 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void debug_pink(char *str)
{
	printf(PINK "%s" RESET_COLOR, str);
}

int	executor(t_cmd_table *table)
{
	if (!table || !table->cmds)
		return (UNKNOWN_ERROR);
	save_original_fd(table);
	table->error_code = execute_cmd_table(table);
	restore_and_close_fds(table);
	return (table->error_code);
}
