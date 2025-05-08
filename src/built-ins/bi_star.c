/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_star.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:18:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/08 11:20:39 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	bi_star(t_cmd_table *table, t_cmd *cmd)
{
	int			pid;
	char *const	command[] = {"telnet", "starwarstel.net", NULL};

	(void)table;
	(void)cmd;
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		execve("/usr/bin/telnet", command, NULL);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	return (0);
}
