/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_weather.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:18:51 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/25 16:37:45 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	bi_weather(t_cmd_table *table, t_cmd *cmd)
{
	int			pid;
	t_list 		*tok;
	char *command[] = {"curl", "wttr.in/", NULL};
	
	(void)table;
	if (cmd->tokens->next)
	{
		tok = cmd->tokens->next;
		command[1] = ft_strjoin(command[1], ((t_tok *)tok->content)->value);
	}
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		execve("/usr/bin/curl", command, NULL);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	return (0);
}
