/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/21 12:11:05 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	executor(t_cmd_table *table)
{
	save_original_fd((table));
	// if (table->is_checker)
	// 	printf("%d: command not found\n", table->error_code);
	// if ((table)->is_checker == false)
		(table)->error_code = execute_cmd_table(table);
	// aqui estaba el freee
	return ((table)->error_code);
}
