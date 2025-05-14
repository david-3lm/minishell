/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:01:42 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/14 21:11:40 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_env_value(char *var_name, t_list *env_lst)
{
	t_env	*env;

	while (env_lst)
	{
		env = (t_env *)env_lst->content;
		if (ft_strcmp(env->key, var_name) == 0)
			return (env->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

char	*expand_variable(char *token, int *i, t_cmd_table *table)
{
	char	*var_name;
	char	*var_value;
	int		start;

	start = ++(*i);
	if (token[*i] == '?')
	{
		table->is_checker = true;
		return (NULL);
	}
	while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
		(*i)++;
	var_name = ft_substr(token, start, *i - start);
	var_value = get_env_value(var_name, *(table->envv));
	if (var_value)
	{
		free(var_name);
		return (ft_strdup(var_value));
	}
	return (ft_strdup(""));
}

char	*append_plain_text(char *token, int *i)
{
	int	start;

	start = *i;
	while (token[*i] && token[*i] != '$')
		(*i)++;
	return (ft_substr(token, start, *i - start));
}

char	*check_expansion(char *token, t_cmd_table *table, t_tok *tok)
{
	char	*result;
	char	*expanded;
	int		i;

	if (!tok->expand)
		return (ft_strdup(token));
	result = ft_calloc(1, sizeof(char));
	table->is_checker = false;
	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
			expanded = expand_variable(token, &i, table);
		else
			expanded = append_plain_text(token, &i);
		if (!expanded && table->is_checker)
		{
			free(result);
			return (NULL);
		}
		result = ft_strjoin_free(result, expanded);
	}
	return (result);
}
