/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:03 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/12/03 15:38:56 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	debug_parser(t_cmd_table *table)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	t_list	*token_list;
	t_tok	*token;
	int		cmd_index;

	if (!table || !table->cmds)
	{
		ft_printf("No commands found in the table.\n");
		return ;
	}

	cmd_list = table->cmds;
	cmd_index = 0;
	ft_printf("=== Command Table Debug ===\n");
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		ft_printf("Command %d:\n", cmd_index);
		if (cmd && cmd->tokens)
		{
			token_list = cmd->tokens;
			while (token_list)
			{
				token = (t_tok *)token_list->content;
				if (token && token->value)
					ft_printf("  Token: [Type: %d, Value: '%s']\n", token->type, token->value);
				token_list = token_list->next;
			}
		}
		else
		{
			ft_printf("  No tokens found for this command.\n");
		}
		cmd_list = cmd_list->next;
		cmd_index++;
	}
	ft_printf("==========================\n");
}


void	add_cmds(t_token_list *tok, t_cmd_table **table)
{
	t_cmd	*current_cmd = NULL;
	t_list	*current_token;
	t_tok	*token_content;
	t_tok	*new_token;

	while (tok->tokens != NULL)
	{
		current_token = tok->tokens;
		token_content = (t_tok *)current_token->content;
		if (!token_content)
			break ;
		if (current_cmd == NULL || (token_content->type != COMMAND && token_content->type != STRING))
		{
			current_cmd = malloc(sizeof(t_cmd));
			if (!current_cmd)
				return ;
			current_cmd->tokens = NULL;
			current_cmd->redirs = NULL;
			ft_lstadd_back(&(*table)->cmds, ft_lstnew(current_cmd));
			(*table)->n_cmd += 1;
		}
		new_token = malloc(sizeof(t_tok));
		if (!new_token)
			return ;
		new_token->type = token_content->type;
		new_token->value = strdup(token_content->value);
		ft_lstadd_back(&(current_cmd->tokens), ft_lstnew(new_token));
		if (token_content->type == PIPE || token_content->type == REDIR)
			current_cmd = NULL;
		tok->tokens = tok->tokens->next;
	}
}


t_error_code	parser(t_token_list *list)
{
	t_cmd_table	*table;

	table = ft_calloc(1, sizeof(t_cmd_table));
	if (!table)
		return (MEM_ALLOC_ERROR);
	table->n_cmd = 0;
	add_cmds(list, &table);
	debug_parser(table);
	return (executor(table));
}
