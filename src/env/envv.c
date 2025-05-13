/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:28:50 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/13 16:08:41 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	*ft_make_env(char *str)
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

static char	*change_shlvl(char *orig_shlvl)
{
	int 	num;
	char	*res;

	num = (int)ft_atoi(orig_shlvl);
	num++;
	res = ft_itoa(num);
	return (res);
}

void	create_env(t_list **list, char *shlvl)
{
	t_env	*env;
	t_env	*env_shlvl;
	char	*pwd;

	env = ft_calloc(1, sizeof(t_env));
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	env->key = ft_strdup("PWD");
	env->value = pwd;
	ft_lstadd_back(list, ft_lstnew(env));
	env_shlvl = ft_calloc(1, sizeof(t_env));
	env_shlvl->key = ft_strdup("SHLVL");
	env_shlvl->value = change_shlvl(shlvl);
	ft_lstadd_back(list, ft_lstnew(env_shlvl));
}

t_list	*env_init(char **orig_envp, char *shlvl)
{
	t_list	*list;
	int		i;

	i = 0;
	list = NULL;
	if (shlvl)
		create_env(&list, shlvl);
	else
	{
		while (orig_envp[i])
		{
			ft_lstadd_back(&list, ft_make_env(orig_envp[i]));
			i++;
		}
	}
	return (list);
}
