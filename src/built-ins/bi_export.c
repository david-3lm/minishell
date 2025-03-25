/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/03/25 16:50:09 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	purge_equal(char *str, t_env **env)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	(*env)->key = ft_substr(str, 0, i);
	(*env)->value = ft_substr(str, i + 1, ft_strlen(str));
	printf("Key => %s\n", (*env)->key);
	printf("Value => %s\n", (*env)->value);
}

void    bi_export(t_cmd_table *table, t_cmd *cmd)
{
	t_list	*env_lst;
	t_env	*env;

	env_lst = table->envv;
	env = malloc(sizeof(t_env));
	purge_equal((char *)cmd->tokens->next->content, &env);
	ft_lstadd_back(&(table->envv), ft_lstnew(env));
	// TODO: si ya existe el token
	// TODO: si no tiene argumentos
}
