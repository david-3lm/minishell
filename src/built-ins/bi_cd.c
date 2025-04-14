/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/14 17:12:04 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd_home(t_cmd_table *table)
{
	char	*path;
	int		error_code;
	printf("no hay argumendoto de cd \n");
	path = mini_get_env(table, "HOME")->value;
	ft_change_old_pwd(table);
	if (!path)
	{
		// revisar codigo de error por aqui
		ft_putendl_fd("minishell : cd: HOME not set", ERROR_E);
		return (1);
	}
	error_code = chdir(path);
	return (error_code);
}

void    bi_cd(t_cmd_table *table, t_cmd *cmd)
{
	char *path;
	t_list *tok;

	printf("estoy haciendo cd builtin \n");
	tok = cmd->tokens->next;
	path = ((t_tok *)tok->content)->value;
	// ft_putendl_fd(path, 2);
	if (!path[0])
		cd_home(table);
	else
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
	printf("old pwd antes --> %s \n", old_pwd->value);
	old_pwd->value = getcwd(old_pwd->value, 0);
	printf("old pwd ahora --> %s \n", old_pwd->value);
}

int	ft_change_path(t_cmd_table *table, char *arg)
{
	int		error_code;
	char	*path;

	/* if (!arg[0])
	{
		printf("no hay argumendoto de cd \n");
		path = mini_get_env(table, "HOME")->value;
		ft_change_old_pwd(table);
		if (!path)
		{
			// revisar codigo de error por aqui
			ft_putendl_fd("minishell : cd: HOME not set", ERROR_E);
			return (1);
		}
	} */
	if (ft_strcmp(arg, "-") == 0)
	{
		printf("el argumento de cd es - \n");
		path = mini_get_env(table, "OLDPWD")->value;
		ft_change_old_pwd(table);
		if (!path)
		{
			// revisar codigo de error por aqui
			ft_putendl_fd("minishell : cd: OLDPWD not set", ERROR_E);
			return (1);
		}
		error_code = chdir(path);
	}
	// TODO: hacer con path absoluto y relativo
	else
	{
		ft_change_old_pwd(table);
		error_code = chdir(arg);
	}
	return (error_code);
}
