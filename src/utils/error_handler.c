/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:50:11 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/25 11:44:17 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

const char	*get_error_msg(t_error_code code)
{
	if (!code)
		return ("");
	if (code == MEM_ALLOC_ERROR)
		return ("Memory allocation failed.");
	if (code == NULL_POINTER_ERROR)
		return ("Null pointer.");
	if (code == UNEXPECTED_EOF)
		return ("Unexpected EOF.");
	if (code == SYNTAX_ERROR)
		return ("Syntax error.");
	if (code == UNKNOWN_ERROR)
		return ("Something went grong. :(");
	return ("");
}