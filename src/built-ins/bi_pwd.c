/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:54:05 by cde-migu          #+#    #+#             */
/*   Updated: 2025/03/25 15:46:12 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// esto no va a funcionar ahora, hayq ue hacer un hueco en la estructura para guardar el pwd

t_error_code	bi_pwd(t_cmd_table *table, t_cmd *cmd)
{
	char	*pwd;
	t_error_code error;
	(void)cmd;
	(void)table;

	error = NO_ERROR;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
	{
		perror("Error");
		error = UNKNOWN_ERROR;
	}
	else
	{
		ft_printf("%s \n", pwd);
		free(pwd);
	}
	return (error);
}