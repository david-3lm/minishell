/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:28:50 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/07 12:57:20 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	*get_env(char *str)
{
	t_env	*env;
	int		i;
	char	*aux;

	i = 0;
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	while (str[i] != '=')
		i++;
	aux = ft_calloc(1, i + 1);
	ft_strlcpy(aux, str, i + 1);
	env->key = ft_strdup(aux);
	free(aux);
	aux = ft_calloc(1, ft_strlen(str) - i + 1);
	ft_strlcpy(aux, &str[i + 1], ft_strlen(str) - i);
	env->value = ft_strdup(aux);
	free(aux);
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
