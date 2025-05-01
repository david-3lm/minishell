/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:01:42 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/01 12:03:57 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(char *var_name, t_list *env_lst)
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

	start = ++(*i); // saltamos el '$'
	if (token[*i] == '?')
	{
		table->is_checker = true;
		return (NULL);
	}
	while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
		(*i)++;
	var_name = ft_substr(token, start, *i - start);
	var_value = get_env_value(var_name, table->envv);
	return (ft_strdup(var_value ? var_value : ""));
}

char	*append_plain_text(char *token, int *i, char *result)
{
	int	start = *i;

	while (token[*i] && token[*i] != '$')
		(*i)++;
	return (ft_strjoin(result, ft_substr(token, start, *i - start)));
}
