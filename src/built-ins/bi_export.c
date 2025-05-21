/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/21 18:31:57 by dlopez-l         ###   ########.fr       */
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
}

bool	token_exists(t_list *env_list, char *str)
{
	t_list	*tmp;
	t_env	*env;

	tmp = env_list;
	while (tmp != NULL)
	{
		env = (t_env *)tmp->content;
		if (env->key != NULL && ft_strcmp(env->key, str) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	change_token(t_list *env_list, t_env *env)
{
	t_list	*tmp;
	t_env	*aux;

	tmp = env_list;
	while (tmp != NULL)
	{
		if (env->key != NULL && \
			ft_strcmp(((t_env *)tmp->content)->key, env->key) == 0)
		{
			aux = tmp->content;
			tmp->content = env;
			free((aux)->key);
			free((aux)->value);
			free(aux);
		}
		tmp = tmp->next;
	}
}

int	manage_correct_export(t_cmd_table *table, t_cmd *cmd, t_env *env)
{
	t_list	*env_lst;

	env_lst = *((table)->envv);
	purge_equal((char *)(cmd->tokens->next->content), &env);
	if (export_manage_inter(env, table))
		return (table->error_code);
	if (token_exists(env_lst, env->key))
		change_token(env_lst, env);
	else
		ft_lstadd_back(((table)->envv), ft_lstnew(env));
	return (table->error_code);
}

int	bi_export(t_cmd_table *table, t_cmd *cmd)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
	{
		check_error(CHECK_VALUE, CHECK_MEM, table);
		return ((table)->error_code);
	}
	if (cmd->tokens->next == NULL)
	{
		manage_empty_export((table));
		free(env);
	}
	else
		table->error_code = manage_correct_export(table, cmd, env);
	return ((table)->error_code);
}
