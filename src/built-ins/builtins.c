/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:19:43 by cde-migu          #+#    #+#             */
/*   Updated: 2025/06/01 19:04:34 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_builtin_idx(char *str, void *builtins[][2])
{
	int	i;

	i = 0;
	while (i < 13)
	{
		if (str)
		{
			if (!ft_strcmp(builtins[i][0], str))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	(*builtin_arr(char *str))(t_cmd_table *table, t_cmd *cmd)
{
	static void	*builtins[][2] = {
	{"echo", bi_echo},
	{"cd", bi_cd},
	{"pwd", bi_pwd},
	{"export", bi_export},
	{"unset", bi_unset},
	{"env", bi_env},
	{"exit", bi_exit},
	{"karol", bi_karol},
	{"star", bi_star},
	{"weather", bi_weather},
	{"moon", bi_moon},
	{"uwu", bi_uwu},
	{"owo", bi_owo}
	};
	int			i;

	i = get_builtin_idx(str, builtins);
	if (i >= 0)
		return (builtins[i][1]);
	return (NULL);
}
