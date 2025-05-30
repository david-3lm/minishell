/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_owo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:23:00 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/30 16:45:11 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	quita_owo(int sig)
{
	(void)sig;
	g_heredoc = 0;
}

int	bi_owo(t_cmd_table *table, t_cmd *cmd)
{
	int			i;
	int			timer;
	const char	*colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};

	(void)table;
	(void)cmd;
	timer = 0;
	i = 0;
	signal(SIGINT, quita_owo);
	while (g_heredoc)
	{
		printf("\033c%s%s", colors[i], OWO);
		while (timer < 100000000)
			timer++;
		timer = 0;
		if (i >= 5)
			i = 0;
		else
			i++;
	}
	g_heredoc = 1;
	printf("\r\033[K" MAGENTA "¡Hasta luego owo!\n");
	return (0);
}
