/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_karol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:18:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/09 15:23:33 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	bi_karol(t_cmd_table *table, t_cmd *cmd)
{
	int			pid;
	char *const	command[] = {"curl", "ascii.live/kitty", NULL};

	(void)table;
	(void)cmd;
	pid = fork();
	if (pid < 0)
		check_error(pid, CHECK_FORK, table);
	else if (pid == 0)
	{
		execve("/usr/bin/curl", command, NULL);
		exit(UNKNOWN_ERROR);
	}
	waitpid(pid, NULL, 0);
	return ((table->error_code));
}
