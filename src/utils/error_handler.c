/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:50:11 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/08 19:22:04 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_error(t_cmd_table *table)
{
	ft_putendl_fd("unset: not enough arguments", ERROR_E);
	table->error_code = UNKNOWN_ERROR;
	return (table->error_code);
}

void	error_handler(int code)
{
	if (code == MEM_ALLOC_ERROR)
		ft_putendl_fd("¿Donde meto yo esto?", ERROR_E);
	if (code == WRONG_CMD_ERROR)
		ft_putendl_fd("💣 Gora Euskal Herria askatuta (reventó la kontxesi) 💣",
			ERROR_E);
	if (code == DUP_ERROR)
		ft_putendl_fd("Error con el DUP (qué es eso?)\n", STDERR_FILENO);
	if (code == FORK_ERROR)
		ft_putendl_fd("Error con el fork 🍝 (con hambre)", STDERR_FILENO);
	if (code == OPEN_ERROR)
		ft_putendl_fd("Error al abrir algo", STDERR_FILENO);
	if (code == CLOSE_ERROR)
		ft_putendl_fd("Error al cerrar algo", STDERR_FILENO);
	if (code == EXECVE_ERROR)
		ft_putendl_fd("EXECVE ERROR (me quedé igual)🌀", STDERR_FILENO);
	if (code == PATH_ERROR)
		ft_putendl_fd("🤨 Path? 🤨", STDERR_FILENO);
	if (code == PIPE_ERROR)
		ft_putendl_fd("Error de pipa (nunca supe como se escribia)", 2);
	if (code == NULL_POINTER_ERROR)
		ft_putendl_fd("↯ Null pointer. ↯", ERROR_E);
	if (code == REDIR_ERROR)
		ft_putendl_fd("Redireccion erronea", ERROR_E);
	if (code == UNKNOWN_ERROR)
		ft_putendl_fd("Ni kontxesi sabe qué ha ido mal ✨ ostia ✨", ERROR_E);
}

void	check_error(int value, int to_check, t_cmd_table *table)
{
	if (value == CHECK_VALUE)
	{
		if (to_check == CHECK_CLOSE)
			table->error_code = CLOSE_ERROR;
		if (to_check == CHECK_OPEN)
			table->error_code = OPEN_ERROR;
		if (to_check == CHECK_DUP)
			table->error_code = DUP_ERROR;
		if (to_check == CHECK_PIPE)
			table->error_code = PIPE_ERROR;
		if (to_check == CHECK_FORK)
			table->error_code = FORK_ERROR;
		if (to_check == CHECK_CMD)
			table->error_code = WRONG_CMD_ERROR;
		error_handler(table->error_code);
	}
}
