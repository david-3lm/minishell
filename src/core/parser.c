/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:03 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/01 14:26:58 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

void	add_cmds(t_token_list *tok, t_cmd_table **table)
{
	t_cmd	*current_cmd;
	t_list	*current_token;

	current_cmd = NULL;
	while (tok->tokens)
	{
		current_token = tok->tokens;
		if (!process_token(&current_cmd, current_token, table))
			return ;
		if (((t_tok *)(tok->tokens->content))->type == PIPE
			|| ((t_tok *)(tok->tokens->content))->type == REDIR)
			current_cmd = NULL;
		tok->tokens = tok->tokens->next;
	}
}

void	count_pipes(t_cmd_table *table)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	t_list	*token_list;
	t_tok	*tok;

	cmd_list = table->cmds;
	table->n_pipes = 0;
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		token_list = cmd->tokens;
		while (token_list)
		{
			tok = (t_tok *)token_list->content;
			if (tok->type == PIPE)
				table->n_pipes += 1;
			if (tok->type == PIPE_ERR)
				table->error_code = PIPE_ERROR;
			token_list = token_list->next;
		}
		cmd_list = cmd_list->next;
	}
}

void	clean_table(t_cmd_table *table)
{
	ft_lstclear(&(table->cmds), free);
	ft_lstclear(&(table->redirs), free);
	table->n_cmd = 0;
	table->n_pipes = 0;
}

t_error_code	parser(t_token_list *list, t_list *envl)
{
	static t_cmd_table	*table;

	if (!table)
		table = ft_calloc(1, sizeof(t_cmd_table));
	else
		clean_table(table);
	if (!table)
		return (MEM_ALLOC_ERROR);
	table->n_cmd = 0;
	table->envv = envl;
	add_cmds(list, &table);
	/*
	LIBERAR LIST TOKEN Y SU CONTENIDO
	*/
	ft_lstclear(&(list->tokens), free);
	free(list);
	debug_parser(table);
	count_pipes(table);
	return (executor(table));
}
