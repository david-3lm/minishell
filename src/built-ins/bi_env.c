/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/03/25 12:43:59 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    bi_env(t_cmd_table *table, t_cmd *cmd)
{
    t_list	*env_lst;
	t_env	*env;
	(void)cmd;

	env_lst = table->envv;
	while (env_lst != NULL)
	{
		env = (t_env *)env_lst->content;
		printf("%s=%s\n", env->key, env->value);
		env_lst = env_lst->next;
	}
} 
