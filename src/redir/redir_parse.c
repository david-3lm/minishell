/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:53:31 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/08 19:44:22 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*alloc_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redirs = NULL;
	return (cmd);
}

bool	set_redir_type(t_redir *redir, const char *val, t_cmd_table *table)
{
	int	sz;

	sz = size_redir((char *)val);
	if (sz == 2)
	{
		if (ft_strncmp(val, ">>", 2) == 0)
			redir->type = RD_SOUT2;
		else
			redir->type = RD_HD;
	}
	else if (sz == 1)
	{
		if (ft_strncmp(val, ">", 1) == 0)
			redir->type = RD_SOUT;
		else
			redir->type = RD_SIN;
	}
	else
	{
		error_handler(REDIR_ERROR);
		table->error_code = REDIR_ERROR;
		return (false);
	}
	return (true);
}

bool	set_redir_direction(t_redir *red, t_list *tok_l, t_cmd_table *table)
{
	if (!tok_l->next)
		return (false);
	red->direction = get_direction((t_tok *)tok_l->next->content);
	if (!red->direction)
	{
		error_handler(REDIR_ERROR);
		table->error_code = REDIR_ERROR;
		return (false);
	}
	return (true);
}

/// @brief Esta funcion crea un comando pero solo rellena redireccion
/// @param tok_list una referencia al token que contiene el <<, >>, ...
/// @return el comando creado
t_cmd	*add_redir(t_list *tok_list, t_cmd_table **table)
{
	t_redir	*redir;
	t_cmd	*cmd;
	t_tok	*tok;

	tok = (t_tok *)tok_list->content;
	if (!tok)
		return (NULL);
	cmd = alloc_cmd();
	redir = alloc_redir();
	if (!cmd || !redir)
		return (NULL);
	if (!set_redir_type(redir, tok->value, *table)
		|| !set_redir_direction(redir, tok_list, *table))
		return (NULL);
	attach_redir(cmd, redir, *table);
	return (cmd);
}
