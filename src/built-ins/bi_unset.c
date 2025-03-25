/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/03/25 16:22:06 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void    bi_unset(t_cmd_table *table, t_cmd *cmd)
{
	// que reciba solo un argumento
	char	*to_unset;
	t_list	*env_lst;
	t_env	*env;
	int		i;

	i = 0;
	env_lst = table->envv;
	to_unset = (char *)cmd->tokens->next->content;
	while (env_lst != NULL)
	{
		env = (t_env *)env_lst->content;
		if (ft_strncmp(to_unset, env->key, ft_strlen(to_unset)) == 0)
			ft_lstdel_index(table->envv, i);
		env_lst = env_lst->next;
		i++;
	}
}

