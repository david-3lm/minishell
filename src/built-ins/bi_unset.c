/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/01 14:57:24 by dlopez-l         ###   ########.fr       */
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
	///////PROTEGER CUANDO SE LLAME UNSET VACIO
	to_unset = (char *)((t_tok *)cmd->tokens->next->content)->value;
	///////////////////

	ft_printf("TENGO QUE UNSETERAR => %s\n", to_unset);
	while (env_lst != NULL)
	{
		env = (t_env *)env_lst->content;
		if (ft_strncmp(to_unset, env->key, ft_strlen(to_unset)) == 0)
		{
			// debug_env(table->envv);
			
			ft_printf("REVISO LA ENV => %s\n", env->key);
			ft_lstdel_index(&table->envv, i);
		}
		env_lst = env_lst->next;
		i++;
	}
}

