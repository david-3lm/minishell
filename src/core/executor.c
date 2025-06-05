/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/06/05 12:02:13 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	review_token(t_cmd_table *table)
{
	t_cmd	*cmd;
	t_list	*list;

	list = table->cmds;
	while (list)
	{
		cmd = (t_cmd *)list->content;
		replace_envs(&(cmd->tokens), cmd->redirs, table);
		cmd->builtin = builtin_arr((char *)cmd->tokens->content);
		list = list->next;
	}
}

int	executor(t_cmd_table *table)
{
	signal(SIGINT, handle_interact);
	signal(SIGQUIT, handle_interact);
	review_token(table);
	(table)->error_code = table_executor(table);
	return ((table)->error_code);
}
