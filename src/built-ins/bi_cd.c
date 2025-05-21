/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/21 19:17:09 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_change_pwd(t_cmd_table *table)
{
	char	*value;
	t_env	*pwd;

	value = NULL;
	pwd = ft_calloc(1, sizeof(t_env));
	value = getcwd(value, 0);
	pwd->key = ft_strdup("PWD");
	pwd->value = ft_strdup(value);
	change_token(*(table)->envv, pwd);
	
	printf("changepwd ---> %s \n", mini_get_env((table), "PWD")->value);
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
	ft_change_old_pwd(table);
	(table)->error_code = chdir(path);
	ft_change_pwd(table);
	return ((table)->error_code);
}

void	ft_change_old_pwd(t_cmd_table *table)
{
	char	*value;
	t_env	*old_pwd;

	value = NULL;
	old_pwd = ft_calloc(1, sizeof(t_env));
	value = getcwd(value, 0);
	old_pwd->key = ft_strdup("OLDPWD");
	old_pwd->value = ft_strdup(value);
	change_token(*(table)->envv, old_pwd);
	printf("changeoldpwd ---> %s \n", mini_get_env((table), "OLDPWD")->value);
	free(value);
}

int	ft_change_path(t_cmd_table *table, char *arg)
{
	char	*path;

	if (ft_strcmp(arg, "-") == 0)
	{
		path = mini_get_env((table), "OLDPWD")->value;
		printf("IF PATH %s\n", path);
		ft_change_old_pwd(table);
		(table)->error_code = chdir(path);
		ft_change_pwd(table);
		printf("if errror codeeeeee ---> %i \n", table->error_code);
		//printf("EL PWD DESPUES DE CHDIR - ---> %s \n", getcwd(pwd, 0));
		//return (ft_change_path(table, path));
	}
	else
	{
		printf("quiero que cambies a este path ---> %s \n", arg);
		ft_change_old_pwd(table);
		(table)->error_code = chdir(arg);
		ft_change_pwd(table);
		printf("else errror codeeeeee ---> %i \n", table->error_code);
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
