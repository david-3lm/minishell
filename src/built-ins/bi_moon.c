/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_moon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:03:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/13 16:50:52 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	bi_moon(t_cmd_table *table, t_cmd *cmd)
{
	int			pid;
	char *const	command[] = {"curl", "wttr.in/moon", NULL};

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
	return (table->error_code);
}
