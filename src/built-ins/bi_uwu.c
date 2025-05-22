/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_uwu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:11:37 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/22 11:40:23 by dlopez-l         ###   ########.fr       */
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
	const char *colors[] = { RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA };
	int	i;
	int timer;

	(void)table;
	(void)cmd;
	timer = 0;
	i = 0;
	signal(SIGINT, quita_uwu);
	while (g_heredoc)
	{
		printf("\r\033[K%s%s", colors[i], UWU);
		while (timer < 10000000)
			timer++;
		timer = 0;
		if (i >= 5)
			i = 0;
		else
			i++;
	}
	g_heredoc = 1;
	printf("\r\033[K" MAGENTA "¡Hasta luego uwu!\n");
	return (0);
}
