/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/08 11:24:54 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd_home(t_cmd_table *table)
{
	char	*path;

	if (mini_get_env(table, "HOME"))
		path = mini_get_env(table, "HOME")->value;
	else
	{
		ft_putendl_fd("kontxesi: cd: HOME not set", ERROR_E);
		(table)->error_code = UNKNOWN_ERROR;
	}
	ft_change_old_pwd(table);
	(table)->error_code = chdir(path);
	return ((table)->error_code);
}

void	ft_change_old_pwd(t_cmd_table *table)
{
	t_env	*old_pwd;
	// t_env	*table_oldpwd;

	old_pwd = mini_get_env(table, "OLDPWD");
	old_pwd->value = getcwd(old_pwd->value, 0);
	change_token(*(table)->envv, old_pwd);
}

int	ft_change_path(t_cmd_table *table, char *arg)
{
	char	*path;

	if (ft_strcmp(arg, "-") == 0)
	{
		if (mini_get_env((table), "OLDPWD"))
			path = mini_get_env((table), "OLDPWD")->value;
		else
		{
			ft_putendl_fd("kontxesi: cd: OLDPWD not set", ERROR_E);
			(table)->error_code = UNKNOWN_ERROR;
			return ((table)->error_code);
		}
		ft_change_old_pwd(table);
		(table)->error_code = chdir(path);
	}
	else
	{
		ft_change_old_pwd(table);
		(table)->error_code = chdir(arg);
	}
	return ((table)->error_code);
}

int	bi_cd(t_cmd_table *table, t_cmd *cmd)
{
	char	*path;
	t_list	*tok;

	tok = cmd->tokens->next;
	if (tok)
		path = ((t_tok *)tok->content)->value;
	else
		(table)->error_code = cd_home(table);
	ft_change_path(table, path);
	return ((table)->error_code);
}
