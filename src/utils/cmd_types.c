/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:37:57 by cde-migu          #+#    #+#             */
/*   Updated: 2025/02/27 11:01:59 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
	HE CREADO ESTE ARCHIVO PARA TENER TODAS LAS FUNCIONES
	DONDE CONSULTO EL TIPO DE UN CMD JUNTAS, AL MENOS DE MOMENTO
 */

t_tok_type	get_next_type(t_list *cmd)
{
	t_list *aux;
	t_tok	*token;
	
	aux = cmd->next;
	token = (t_tok *)aux->content;
	return (token->type);
}

t_tok_type get_token_type(t_list *cmd)
{
	t_tok *token;

	token = (t_tok *)cmd->content;
	return (token->type);
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

/* int	count_redirs(t_cmd_table *table)
{
	int		count;
	t_list	*cmd_list;
	t_cmd	*cmd;

	count = 0;
	cmd_list = table->cmds;
	cmd = (t_cmd *)cmd_list->content;
	while (cmd_list)
	{	
		if (((t_tok *)cmd->tokens)->type == REDIR)
			count++;
		cmd_list = cmd_list->next;
	}
	return (count);
} */

bool	is_pipe(t_cmd cmd)
{
	t_tok 	*token;
	t_list	*token_list;

	token_list = cmd.tokens;
	token = (t_tok *)token_list->content;
	if (token && token->type == 4)
		return (true);
	else
		return (false);
}

bool	is_redir(t_cmd cmd)
{
	t_tok 	*token;
	t_list	*token_list;

	token_list = cmd.tokens;
	token = (t_tok *)token_list->content;
	if (token && token->type == REDIR)
		return (true);
	else
		return (false);
}