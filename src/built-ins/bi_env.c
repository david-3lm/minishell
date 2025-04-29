/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/29 17:38:52 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	bi_env(t_cmd_table *table, t_cmd *cmd)
{
	t_list	*env_lst;
	t_env	*env;

	(void)cmd;
	env_lst = table->envv;
	while (env_lst != NULL)
	{
		env = (t_env *)env_lst->content;
		if (ft_strcmp(env->value, ""))
			printf("%s=%s\n", env->key, env->value);
		env_lst = env_lst->next;
	}
	table->error_code = NO_ERROR;
	return (table->error_code);
}

t_env	*mini_get_env(t_cmd_table *table, char *var)
{
	t_list	*env_lst;
	t_env	*env;

	env_lst = table->envv;
	while (env_lst != NULL)
	{
		env = (t_env *)env_lst->content;
		if (ft_strncmp(var, env->key, ft_strlen(var)) == 0)
			return (env);
		env_lst = env_lst->next;
	}
	return (NULL);
}
