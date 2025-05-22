/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:19:43 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/22 11:12:40 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	{"uwu", bi_uwu}
	};
	int			i;

	i = 0;
	while (i < 12)
	{
		if (str)
		{
			if (!ft_strncmp(builtins[i][0], str, ft_strlen(str)))
				return (builtins[i][1]);
		}
		i++;
	}
	return (NULL);
}
