/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/08 18:05:13 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
	static void		print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}
 */

void    bi_cd(t_cmd_table *table, t_cmd *cmd)
{
	char *path;
	t_list *tok;
	
	tok = cmd->tokens;
	path = ((t_tok *)tok->content)->value;
	ft_change_path(table, path);
	/* if (cd_ret < 0)
			cd_ret *= -1;
	if (cd_ret != 0)
			print_error(args);
		TODO: GESTIONAR CODIGOS DE ERROR
	*/
}

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
	else
	{
		ft_change_old_pwd(table);
		error_code = chdir(arg);
	}
	error_code = chdir(path);
	return (error_code);
}
