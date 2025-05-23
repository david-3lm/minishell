/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_weather.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:18:51 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/09 15:22:42 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	bi_weather(t_cmd_table *table, t_cmd *cmd)
{
	int			pid;
	char *const	command[] = {"curl", "wttr.in/", NULL};

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
