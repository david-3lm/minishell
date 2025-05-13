/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:54:08 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/13 16:58:37 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_manage_inter(t_env *env, t_cmd_table *table)
{
	if (ft_strchr(env->key, '?') != 0)
	{
		ft_error_export(table, env->key);
		free(env->key);
		free(env->value);
		free(env);
		return (table->error_code);
	}
	else
		return (false);
}

void	manage_empty_export(t_cmd_table *table)
{
	t_list	*tmp;
	t_env	*env;

	tmp = *table->envv;
	while (tmp != NULL)
	{
		env = (t_env *)tmp->content;
		ft_printf("declare -x %s=%s\n", env->key, env->value);
		tmp = tmp->next;
	}
}
