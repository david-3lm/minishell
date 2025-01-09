/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/01/09 18:59:00 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void prueba_test(void)
{
	ft_printf("hola");
}

bool	is_command(t_cmd cmd)
{
	t_tok 	*token;
	t_list	*token_list;

	token_list = cmd.tokens;
	token = (t_tok *)token_list->content;
	if (token && token->type == 0)
		return (true);
	else
		return (false);
}

t_error_code	executor(t_cmd_table *table)
{
	t_list	*cmd_list;
	int		cmd_index;
	t_cmd	*cmd;

	cmd_index = 0;
	cmd_list = table->cmds;
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (is_command(cmd))
			path_exec(cmd);
		cmd_list = cmd_list->next;
		cmd_index++;
	}
	(void )table;
	return (EXIT_SUCCESS);
}
// 