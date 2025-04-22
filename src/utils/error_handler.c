/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:50:11 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/22 16:03:51 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void error_handler(t_cmd_table *table)
{
	// TODO: con todos los errores, ajustar los mensajes de error
	// llamar a esta funcion en todos los sitios donde hagamos gestion de errores
	int	code;

	code = table->error_code;
	if (code == NO_ERROR)
		return ;
	if (code == MEM_ALLOC_ERROR)
		ft_putendl_fd("Memory allocation failed.", ERROR_E);
	if (code == WRONG_CMD_ERROR)
		ft_putendl_fd("Gora Euskal Herria askatuta", ERROR_E);
	if (code == DUP_ERROR)
		ft_putendl_fd("Process terminated with dup error\n", STDERR_FILENO);
	if (code == FORK_ERROR)
		ft_putendl_fd("Process terminated with fork error", STDERR_FILENO);
	if (code == OPEN_ERROR)
		ft_putendl_fd("Process terminated with open error", STDERR_FILENO);
	if (code == CLOSE_ERROR)
		ft_putendl_fd("Process terminated with close error", STDERR_FILENO);
	if (code == EXECVE_ERROR)
		ft_putendl_fd("Process terminated with execve error", STDERR_FILENO);
	if (code == PATH_ERROR)
		ft_putendl_fd("Process terminated with path error", STDERR_FILENO);
	if (code == PIPE_ERROR)
		ft_putendl_fd("Process terminated with pipe error", STDERR_FILENO);
	if (code == NULL_POINTER_ERROR)
		ft_putendl_fd("Null pointer.", ERROR_E);
	if (code == UNKNOWN_ERROR)
		ft_putendl_fd("Something went grong. :(", ERROR_E);
	exit(code);
}
