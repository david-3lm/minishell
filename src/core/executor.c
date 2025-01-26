/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:34:06 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/01/26 16:01:13 by cde-migu         ###   ########.fr       */
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
int	command_exec(t_cmd *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (ft_error("Fork: "));
	if (pid == 0)
		path_exec(cmd);
	else
		waitpid(pid, &status, 0);
	if (status && WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (NO_ERROR);
}

t_error_code	executor(t_cmd_table *table)
{
	t_list	*cmd_list;
	int		cmd_index;
	t_error_code	res;
	t_cmd	*cmd;

	cmd_index = 0;
	cmd_list = table->cmds;
	res = NO_ERROR;
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (is_command(*cmd) && get_next_type(cmd_list) == PIPE)
		{
			// pipex(table);
			cmd_list = cmd_list->next;
		}
		else
			res = command_exec(cmd);
		cmd_list = cmd_list->next;
		cmd_index++;
	}
	(void )table;
	return (res);
}
