/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:37:57 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/13 16:30:55 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tok_type	get_token_type(t_list *cmd)
{
	t_tok	*token;

	token = (t_tok *)cmd->content;
	return (token->type);
}

bool	is_command(t_cmd cmd)
{
	t_tok	*token;
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
	t_tok	*token;
	t_list	*token_list;

	token_list = cmd.tokens;
	token = (t_tok *)token_list->content;
	if (token && token->type == STRING)
		return (true);
	else
		return (false);
}

bool	is_redir(t_cmd cmd)
{
	t_tok	*token;
	t_list	*token_list;

	token_list = cmd.tokens;
	token = (t_tok *)token_list->content;
	if (token && token->type == REDIR)
		return (true);
	else
		return (false);
}
