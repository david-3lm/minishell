/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:34:24 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/21 15:14:46 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_error(t_cmd_table *table)
{
	ft_putendl_fd("unset: not enough arguments", ERROR_E);
	table->error_code = UNKNOWN_ERROR;
	return (table->error_code);
}

void	ft_wrong_access_error(t_cmd_table *table, char *cmd, int code)
{
	ft_putstr_fd("💣 ", ERROR_E);
	perror(cmd);
	table->error_code = code;
}

void	ft_error_str(t_cmd_table *table, char *str)
{
	ft_putstr_fd("💣 ", ERROR_E);
	ft_putstr_fd(str, ERROR_E);
	ft_putendl_fd(": command not found", ERROR_E);
	table->error_code = WRONG_CMD_ERROR;
}

void	ft_error_export(t_cmd_table *table, char *str)
{
	ft_putstr_fd("💣Kontxesi: export: '", ERROR_E);
	ft_putstr_fd(str, ERROR_E);
	ft_putendl_fd("': not a valid identifier", ERROR_E);
	table->error_code = UNKNOWN_ERROR;
}
