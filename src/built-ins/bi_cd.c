/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/30 16:42:55 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_change_env(t_cmd_table *table, char *key, char *path, bool is_path)
{
	char	*value;
	t_env	*new_env;

	value = NULL;
	new_env = ft_calloc(1, sizeof(t_env));
	if ((ft_strcmp("OLDPWD", key) == 0) && (is_path == true))
		new_env->value = ft_strdup(path);
	else
	{
		value = getcwd(value, 0);
		new_env->value = ft_strdup(value);
	}
	change_token(*(table)->envv, new_env);
	free(value);
}

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
	ft_change_env(table, "OLDPWD", NULL, false);
	(table)->error_code = chdir(path);
	ft_change_env(table, "PWD", NULL, false);
	return ((table)->error_code);
}

int	ft_change_path(t_cmd_table *table, char *arg)
{
	char	*path;
	char	*aux;

	path = NULL;
	if (ft_strcmp(arg, "-") == 0)
	{
		path = mini_get_env((table), "OLDPWD")->value;
		aux = mini_get_env((table), "PWD")->value;
		(table)->error_code = chdir(path);
		ft_change_env(table, "OLDPWD", aux, true);
		ft_change_env(table, "PWD", path, false);
	}
	else
	{
		ft_change_env(table, "OLDPWD", path, false);
		(table)->error_code = chdir(arg);
		ft_change_env(table, "PWD", path, false);
	}
	return ((table)->error_code);
}

int	bi_cd(t_cmd_table *table, t_cmd *cmd)
{
	char	*path;
	t_list	*tok;

	tok = cmd->tokens->next;
	if (tok)
		path = (char *)tok->content;
	else
	{
		(table)->error_code = cd_home(table);
		return ((table)->error_code);
	}
	ft_change_path(table, path);
	return ((table)->error_code);
}
