/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:08 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/19 12:58:31 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tok_type	get_ttype(char *tok)
{
	if (ft_strnstr(tok, "<", 4) || ft_strnstr(tok, ">", 4) || ft_strnstr(tok, ">>", 8))
		return (REDIR);
	if (ft_strnstr(tok, "|", 4))
		return (PIPE);
	if (ft_strnstr(tok, "$", 1))
		return (VARIABLE);
	if (tok[0] == '\'' || tok[0] == '"')
		return (STRING);
	return (COMMAND);
}

void	add_token(t_token_list *list, char *value)
{
	t_tok	*new_tok;

	new_tok = malloc(sizeof(t_tok));
	if (!new_tok)
		return ;
	new_tok->type = get_ttype(value);
	new_tok->value = ft_strdup(value);
	ft_lstadd_back(&(list->tokens), ft_lstnew(new_tok));
}

t_token_list	*lexer(char *input)
{
	t_token_list	*list;
	char			**sp;
	int				i;

	sp = ft_split_set(input, " 	\n");
	i = 0;
	list = ft_calloc(1, sizeof(t_token_list));
	if (!list)
		return (NULL);
	while (sp[i])
	{
		add_token(list, sp[i]);
		i++;
	}
	return (list);
}
