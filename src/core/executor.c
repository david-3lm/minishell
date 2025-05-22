/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/22 11:47:45 by dlopez-l         ###   ########.fr       */
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
	// save_original_fd((table));
	// if (table->is_checker)
	// 	printf("%d: command not found\n", table->error_code);
	// if ((table)->is_checker == false)
	review_token(table);
	debug_table(table);
		(table)->error_code = execute_cmd_table(table);
	// aqui estaba el freee
	return ((table)->error_code);
}
