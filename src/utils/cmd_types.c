/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:37:57 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/29 15:32:40 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
	HE CREADO ESTE ARCHIVO PARA TENER TODAS LAS FUNCIONES
	DONDE CONSULTO EL TIPO DE UN CMD JUNTAS, AL MENOS DE MOMENTO
 */

/* bool	is_pipe_correct(t_list *cmd_list)
{
	t_list	*aux;
	t_cmd	*current;
	t_cmd	*next;
	t_cmd	*two_next;

	aux = cmd_list;
	current = (t_cmd *)aux->content;
	next = (t_cmd *)aux->next->content;
	two_next = (t_cmd *)aux->next->next->content;
	if (is_command(*current) && is_pipe(*next) && is_command(*two_next))
		return (true);
	else
		return (false);
}
 */

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
	if (token && token->type == COMMAND)
		return (true);
	else
		return (false);
}

bool	is_str(t_cmd cmd)
{
	t_tok 	*token;
	t_list	*token_list;

	token_list = cmd.tokens;
	token = (t_tok *)token_list->content;
	if (token && token->type == STRING)
		return (true);
	else
		return (false);
}

bool	is_pipe(t_cmd cmd)
{
	t_tok 	*token;
	t_list	*token_list;

	token_list = cmd.tokens;
	token = (t_tok *)token_list->content;
	if (token && token->type == PIPE)
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
