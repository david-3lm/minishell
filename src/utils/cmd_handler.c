/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:35:13 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/30 16:52:31 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	need_new_cmd(t_cmd *current_cmd, int tok_type)
{
	return (current_cmd == NULL
		|| (tok_type != COMMAND && tok_type != STRING));
}

t_cmd	*create_or_redir_cmd(t_list *current_token, t_cmd_table **table)
{
	t_tok	*tc;
	t_cmd	*cmd;

	tc = (t_tok *)current_token->content;
	if (tc->type == REDIR)
		return (add_redir(current_token, table));

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redirs = NULL;
	cmd->builtin = builtin_arr(tc->value);
	return (cmd);
}

void	attach_cmd_to_table(t_cmd *cmd, t_cmd_table **table)
{
	cmd->tokens = NULL;
	ft_lstadd_back(&(*table)->cmds, ft_lstnew(cmd));
	(*table)->n_cmd += 1;
}

t_tok	*copy_and_expand(t_tok *orig, t_cmd_table *table)
{
	t_tok	*new_tok;

	new_tok = malloc(sizeof(t_tok));
	if (!new_tok)
		return (NULL);
	new_tok->type = orig->type;
	new_tok->value = check_expansion(orig->value, table, orig);
	if (!new_tok->value)
		new_tok->type = VARIABLE;
	return (new_tok);
}

bool	process_token(t_cmd **current_cmd, t_list *curr_t, t_cmd_table **table)
{
	t_tok	*tok_content;
	t_tok	*new_tok;

	tok_content = (t_tok *)curr_t->content;
	if (!tok_content)
		return (false);
	if (need_new_cmd(*current_cmd, tok_content->type))
	{
		*current_cmd = create_or_redir_cmd(curr_t, table);
		if (!*current_cmd)
			error_handler(WRONG_CMD_ERROR);
		attach_cmd_to_table(*current_cmd, table);
	}
	new_tok = copy_and_expand(tok_content, *table);
	if (!new_tok)
		return (false);
	ft_lstadd_back(&(*current_cmd)->tokens, ft_lstnew(new_tok));
	return (true);
}
