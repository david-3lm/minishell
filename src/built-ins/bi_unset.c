/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/08 19:22:34 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	del_env(void *value)
{
	t_env	*env;

	env = (t_env *)value;
	free(env->key);
	free(env->value);
	free(value);
}

int	bi_unset(t_cmd_table *table, t_cmd *cmd)
{
	char	*to_unset;
	t_list	*env_lst;
	t_env	*env;
	int		i;

	i = 0;
	env_lst = *(table)->envv;
	if (!(t_tok *)cmd->tokens->next)
		return (unset_error(table));
	to_unset = (char *)((t_tok *)cmd->tokens->next->content)->value;
	while (env_lst != NULL)
	{
		env = (t_env *)(env_lst->content);
		if (ft_strncmp(to_unset, env->key, ft_strlen(to_unset)) == 0)
		{
			ft_lstdel_index(((table)->envv), i, del_env);
			break ;
		}
		env_lst = env_lst->next;
		i++;
	}
	return ((table)->error_code);
}
