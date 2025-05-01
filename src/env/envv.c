/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:28:50 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/01 11:46:52 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	*get_env(char *str)
{
	t_env	*env;
	int		i;

	i = 0;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	while (str[i] != '=')
		i++;
	env->key = malloc(i + 1);
	env->value = malloc(ft_strlen(str) - i + 1);
	ft_strlcpy(env->key, str, i + 1);
	ft_strlcpy(env->value, &str[i + 1], ft_strlen(str) - i);
	return (ft_lstnew(env));
}

t_list	*env_init(char **orig_envp)
{
	t_list	*list;
	int		i;

	i = 0;
	list = NULL;
	while (orig_envp[i])
	{
		ft_lstadd_back(&list, get_env(orig_envp[i]));
		i++;
	}
	return (list);
}
