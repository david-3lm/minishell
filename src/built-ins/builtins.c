/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:19:43 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/25 15:49:30 by cde-migu         ###   ########.fr       */
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
	};
	// cambiar los nombres por los nombres de mis funciones
	// cómo juntar esto con el resto de la ejecucion??
	// hacer que retornen códigos de error
	int			i;

	i = 0;
	while (i < 9)
	{
		if (str)
		{
			if (!ft_strncmp(builtins[i][0], str, ft_strlen(builtins[i][0])))
				return (builtins[i][1]);
		}
		i++;
	}
	return (NULL);
}
