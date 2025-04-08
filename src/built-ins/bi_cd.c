/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/08 15:57:36 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
	- sin argumentos te lleva a HOME;
	- 
 */

void    bi_cd(t_cmd_table *table, t_cmd *cmd)
{
	char *path;
	t_list *tok;
	
	tok = cmd->tokens;
	path = ((t_tok *)tok->content)->value;
	ft_change_path(table, path);
	
}

/* 
	- primero coger las variabs de entorno pwd y old pwd
	- modificar valor de oldpwd por el valor actual antes de cambiar de direccion
	- si cd no tiene argumento, redirigir a donde señala HOME
	- 
 */

void	ft_change_old_pwd(t_cmd_table *table)
{
	t_env	*old_pwd;

	old_pwd = mini_get_env(table, "OLDPWD");
	old_pwd->value = getcwd(old_pwd->value, 0);
}

int	ft_change_path(t_cmd_table *table, char *arg)
{
	int		error_code;
	char	*path;

	if (!arg[0])
	{
		path = mini_get_env(table, "HOME")->value;
		ft_change_old_pwd(table);
		if (!path)
		{
			// revisar codigo de error por aqui
			ft_putendl_fd("minishell : cd: HOME not set", ERROR_E);
			return (1);
		}
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		path = mini_get_env(table, "OLDPWD")->value;
		ft_change_old_pwd(table);
		if (!path)
		{
			// revisar codigo de error por aqui
			ft_putendl_fd("minishell : cd: OLDPWD not set", ERROR_E);
			return (1);
		}
	}
	// TODO: hacer con path absoluto y relativo
	error_code = chdir(path);
	return (error_code);
}
