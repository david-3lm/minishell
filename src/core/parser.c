/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:03 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/20 21:09:54 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_cmds(t_token_list *tok, t_cmd_table *table)
{
	t_cmd *new_cmd;

	while (tok->tokens->next != NULL)
	{
		if (table->cmds[0].content == NULL)
		{		
			new_cmd = malloc(sizeof(t_cmd));
			if (!new_cmd)
				return ;
			new_cmd->tokens = tok->tokens->content;
			ft_lstadd_back(&(table->cmds), ft_lstnew(new_cmd));
		}
		tok->tokens = tok->tokens->next;
	}
}

t_cmd_table	*parser(t_token_list *list)
{
	t_cmd_table *table;

	table = ft_calloc(1, sizeof(t_cmd_table));
	if (!table)
		return (NULL);
	add_cmds(list, table);
	// ft_printf("%s\n", table->cmds->content);
	return (table);
}