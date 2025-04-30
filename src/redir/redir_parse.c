/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:53:31 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/30 17:01:02 by dlopez-l         ###   ########.fr       */
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

t_redir	*alloc_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	return (redir);
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

void	attach_redir(t_cmd *cmd, t_redir *redir, t_cmd_table *table)
{
	ft_lstadd_back(&cmd->redirs, ft_lstnew(redir));
	ft_lstadd_back(&table->redirs, ft_lstnew(redir));
}
