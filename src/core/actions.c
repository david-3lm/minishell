/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:00:57 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/30 19:31:20 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_signal(int signal)
{
	if (!g_heredoc && signal == SIGINT)
		g_heredoc = 1;
	else if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_interact(int signal)
{
	if (!g_heredoc && signal == SIGINT)
		g_heredoc = 1;
	write(1, "\n", 1);
}
