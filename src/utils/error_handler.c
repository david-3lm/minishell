/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:50:11 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/25 14:59:01 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void error_handler(int code)
{
	// TODO: con todos los errores, ajustar los mensajes de error
	// TODO: ERROR si encuentra por ejemplo | | (dos pipes seguidos separados en dos tokens)
	// llamar a esta funcion en todos los sitios donde hagamos gestion de errores
	if (code == NO_ERROR)
		return ;
	if (code == MEM_ALLOC_ERROR)
		ft_putendl_fd("¿Donde meto yo esto?", ERROR_E);
	if (code == WRONG_CMD_ERROR)
		ft_putendl_fd("💣 Gora Euskal Herria askatuta (reventó la kontxesi) 💣", ERROR_E);
	if (code == DUP_ERROR)
		ft_putendl_fd("Error con el DUP (qué es eso?)\n", STDERR_FILENO);
	if (code == FORK_ERROR)
		ft_putendl_fd("Error con el fork 🍝 (te quedas con hambre)", STDERR_FILENO);
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
