/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:14:29 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/24 18:10:08 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tok_type	get_ttype(char *tok)
{
	if (ft_strchr(tok, '<') || ft_strchr(tok, '>'))
		return (REDIR);
	if (ft_strchr(tok, '|'))
		return (PIPE);
	if (tok[0] == '\'' || tok[0] == '"')
		return (STRING);
	if (ft_strchr(tok, '$'))
		return (COMMAND);
	return (COMMAND);
}

bool is_quote(char c) {
    return (c == '"' || c == '\'');
}

int	count_quotes(char *str)
{
	int		i;
	int		count;
	char	q;

	i = 0;
	count = 0;
	q = ' ';
	while (str[i] != '\0')
	{
		if (q == ' ' && (str[i] == '\'' || str[i] == '"'))
			q = str[i];
		if (q == str[i])
			count++;
		i++;
	}
	return (count);
}

void	add_token(t_token_list *list, char *value)
{
	t_tok	*new_tok;

	new_tok = malloc(sizeof(t_tok));
	if (!new_tok)
		return ;
	new_tok->expand = 1;
	new_tok->type = get_ttype(value);
	if (new_tok->type == STRING && count_quotes(value) == 2)
	{
		if (value[0] == '\'')
			new_tok->expand = 0;
		new_tok->value = ft_substr(value, 1, ft_strlen(value) - 2);
	}
	else if (new_tok->type == STRING && count_quotes(value) != 2)
	{
		new_tok->value = ft_substr(value, 1, ft_strlen(value) - 2);
		printf("Falta una quote\n"); //AQUI DEVOLVER ERROR
		return ;
	}
	else
		new_tok->value = ft_strdup(value);
	ft_lstadd_back(&(list->tokens), ft_lstnew(new_tok));
}
