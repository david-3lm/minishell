/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:03 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/05 12:25:34 by dlopez-l         ###   ########.fr       */
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
	current_token = tok->tokens;
	while (current_token)
	{
		printf("AÑADIMOS TOKEN\n");
		if (!process_token(&current_cmd, current_token, table))
			return ;
		if (((t_tok *)(current_token->content))->type == PIPE
			|| ((t_tok *)(current_token->content))->type == REDIR)
			current_cmd = NULL;
		current_token = current_token->next;
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

t_error_code	parser(t_token_list *list, t_list *envl)
{
	static t_cmd_table	*table;
	t_cmd_table			*aux;

	if (!table)
		table = ft_calloc(1, sizeof(t_cmd_table));
	else
	{
		aux = ft_calloc(1, sizeof(t_cmd_table));
		aux->error_code = table->error_code;
		free(table);
		table = aux;
	}
	if (!table)
		return (MEM_ALLOC_ERROR);
	table->n_cmd = 0;
	table->envv = envl;
	add_cmds(list, &table);
	free_token_list(list->tokens);
	free(list);
	debug_parser(table);
	count_pipes(table);
	return (executor(table));
}
