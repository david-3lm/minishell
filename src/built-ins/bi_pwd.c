/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:54:05 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/07 14:57:10 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	bi_pwd(t_cmd_table **table, t_cmd *cmd)
{
	char	*pwd;
	// t_env	*env;

	(void)cmd;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	// env = mini_get_env((*table), "PWD");
	if (pwd)
	{
		// pwd = env->value;
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
	}
	else
	{
		ft_putendl_fd("Error: kontxesi: getcwd", ERROR_E);
		(*table)->error_code = UNKNOWN_ERROR;
	}
	return ((*table)->error_code);
}
