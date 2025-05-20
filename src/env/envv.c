/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:28:50 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/20 12:15:09 by cde-migu         ###   ########.fr       */
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
	int		num;
	char	*res;

	num = (int)ft_atoi(orig_shlvl);
	num++;
	res = ft_itoa(num);
	return (res);
}

t_env	*ft_create_env(char *key, char *value)
{
	t_env *env;
	env = ft_calloc(1, sizeof(t_env));
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	return (env);
}

void	generate_env(t_list **list, char *shlvl)
{
	char	*pwd;
	char	*lvl;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	ft_lstadd_back(list, ft_lstnew(ft_create_env("PWD", pwd)));
	free(pwd);
	lvl = change_shlvl(shlvl);
	ft_lstadd_back(list, ft_lstnew(ft_create_env("SHLVL", lvl)));
	free(lvl);
	ft_lstadd_back(list, ft_lstnew(ft_create_env("PATH", K_PATH)));
}


t_list	*env_init(char **orig_envp, char *shlvl)
{
	t_list	*list;
	int		i;

	i = 0;
	list = NULL;
	if (shlvl)
		generate_env(&list, shlvl);
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
