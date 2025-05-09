/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/09 15:49:39 by cde-migu         ###   ########.fr       */
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
	// printf("Key => %s\n", (*env)->key);
	// printf("Value => %s\n", (*env)->value);
}

bool	token_exists(t_list *env_list, char *str)
{
	t_list	*tmp;
	t_env	*env;

	tmp = env_list;
	while (tmp != NULL)
	{
		env = (t_env *)tmp->content;
		ft_printf("%s:%d: %s\n", __FILE__, __LINE__, env->key);
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

int	bi_export(t_cmd_table *table, t_cmd *cmd)
{
	t_list	*env_lst;
	t_env	*env;

	env_lst = *((table)->envv);
	env = malloc(sizeof(t_env));
	// ft_printf("Env => %s\n", ((t_env *)env_lst->content)->key);
	if (!env)
	{
		(table)->error_code = UNKNOWN_ERROR;
		return ((table)->error_code);
	}
	if (cmd->tokens->next == NULL)
	{
		manage_empty_export((table));
		free(env);
	}
	else
	{
		purge_equal(((t_tok *)cmd->tokens->next->content)->value, &env);
		if (token_exists(env_lst, env->key))
			change_token(env_lst, env);
		else
			ft_lstadd_back(((table)->envv), ft_lstnew(env));
	}
	return ((table)->error_code);
}
