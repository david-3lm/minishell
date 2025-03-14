/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:54:05 by cde-migu          #+#    #+#             */
/*   Updated: 2025/03/14 12:17:33 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// esto no va a funcionar ahora, hayq ue hacer un hueco en la estructura para guardar el pwd

t_error_code	bi_pwd(void)
{
	char	*pwd;
	t_error_code error;

	error = NO_ERROR;
	pwd = getcwd(cwd, 0);
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