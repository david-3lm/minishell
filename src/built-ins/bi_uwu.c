/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_uwu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:11:37 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/06/03 12:39:00 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	quita_uwu(int sig)
{
	(void)sig;
	g_heredoc = 0;
}

int	bi_uwu(t_cmd_table *table, t_cmd *cmd)
{
	int			i;
	int			timer;
	const char	*colors[] = {RED, GREEN, RESET_COLOR};

	(void)table;
	(void)cmd;
	timer = 0;
	i = 0;
	signal(SIGINT, quita_uwu);
	while (g_heredoc)
	{
		printf("\033c%s%s", colors[i], UWU);
		while (timer < 100000000)
			timer++;
		timer = 0;
		if (i >= 2)
			i = 0;
		else
			i++;
	}
	g_heredoc = 1;
	printf("\r\033[K" MAGENTA "¡Hasta luego uwu!\n");
	return (0);
}
