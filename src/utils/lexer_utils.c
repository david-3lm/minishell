/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:14:29 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/30 16:14:27 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tok_type	get_ttype(char *tok)
{
	if (tok[0] == '\'' || tok[0] == '"')
		return (STRING);
	if (ft_strchr(tok, '<') || ft_strchr(tok, '>'))
		return (REDIR);
	if (ft_strchr(tok, '|'))
		return (PIPE);
	if (ft_strchr(tok, '$'))
		return (COMMAND);
	return (COMMAND);
}

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

bool	is_separator(char c)
{
	return (c == ' ' || c == '\t');
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

int	count_char(char *str, char c)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
