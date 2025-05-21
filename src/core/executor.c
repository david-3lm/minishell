/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/21 12:04:09 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	executor(t_cmd_table *table)
{
	save_original_fd((table));
	if (table->is_checker)
		printf("%d: command not found\n", table->error_code);
	if ((table)->is_checker == false)
		(table)->error_code = execute_cmd_table(table);
	free_cmd_table((table));
	return ((table)->error_code);
}
