/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:06:13 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/04 13:34:37 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_token_list(t_list *tokens)
{
	t_list	*tmp;
	t_tok	*tok;

	while (tokens)
	{
		tmp = tokens->next;
		tok = (t_tok *)tokens->content;
		free(tok->value);
		free(tok);
		free(tokens);
		tokens = tmp;
	}
}


void	free_redir_list(t_list *lst)
{
	t_list	*tmp;
	t_redir	*redir;

	while (lst)
	{
		tmp = lst->next;
		redir = (t_redir *)lst->content;
		if (redir)
		{
			free(redir->direction);
			free(redir);
		}
		free(lst);
		lst = tmp;
	}
}

void	free_cmd_list(t_list *lst)
{
	t_list	*tmp;
	t_cmd	*cmd;

	while (lst)
	{
		tmp = lst->next;
		cmd = (t_cmd *)lst->content;
		if (cmd)
		{
			free_token_list(cmd->tokens);
			free_redir_list(cmd->redirs);
			free(cmd);
		}
		free(lst);
		lst = tmp;
	}
}

void	free_cmd_table(t_cmd_table *table)
{
	if (!table)
		return ;
	free_cmd_list(table->cmds);
	// No es necesario liberar `table->delimiter` (no lo usas)
	// TODO: liberar `table->pipes` si llegas a usarlos
	ft_lstclear(&table->pids, free);
	free_redir_list(table->redirs);
	ft_lstclear(&table->envv, free); // Solo si `envv->content` se libera con `free`
}

