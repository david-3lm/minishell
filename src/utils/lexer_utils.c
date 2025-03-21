/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:14:29 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/19 21:38:55 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tok_type	get_ttype(char *tok)
{
	if (ft_strchr(tok, '<') || ft_strchr(tok, '>'))
		return (REDIR);
	if (ft_strchr(tok, '|'))
		return (PIPE);
	if (ft_strchr(tok, '$'))
		return (VARIABLE);
	if (tok[0] == '\'' || tok[0] == '"')
		return (STRING);
	return (COMMAND);
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
	new_tok->type = get_ttype(value);
	if (new_tok->type == STRING && count_quotes(value) == 2)
		new_tok->value = ft_substr(value, 1, ft_strlen(value) - 2);
	else if (new_tok->type == STRING && count_quotes(value) != 2)
	{
		new_tok->value = ft_substr(value, 1, ft_strlen(value) - 2);
		printf("Falta una quote\n"); //AQUI DEVOLVER ERROR
	}
	else
		new_tok->value = ft_strdup(value);
	ft_lstadd_back(&(list->tokens), ft_lstnew(new_tok));
}
