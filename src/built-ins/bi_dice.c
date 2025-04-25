/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_dice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:54:38 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/25 15:59:41 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	bi_dice(t_cmd_table *table, t_cmd *cmd)
{
	const int		fd = open("/dev/random", O_RDONLY, 0);
	unsigned int	a;
	char const *matrix[] = {
		
	};
	
	read(fd, &a, sizeof(a));
	imprimir(matrix[a % 6]);
}