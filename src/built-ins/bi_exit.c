/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:58:31 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/14 15:21:44 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bi_exit(t_cmd_table *table, t_cmd *cmd)
{
	(void)cmd;
	(void)table;
	printf("estoy haciendo exit builtin \n");
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(EXIT_SUCCESS);
	// exit libera? o tengo que liberar yo cosas?
}