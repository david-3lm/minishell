/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:08 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/27 12:33:00 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quotes_are_closed(const char *input)
{
	int		i;
	char	open_quote;

	i = 0;
	open_quote = '\0';
	while (input[i])
	{
		if (!open_quote && (input[i] == '\'' || input[i] == '"'))
			open_quote = input[i];
		else if (open_quote && input[i] == open_quote)
			open_quote = '\0';
		i++;
	}
	return (open_quote == '\0');
}

void	purge_input(t_token_list *list, const char *str)
{
	char	*aux;
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (str[i])
	{
		while (str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i])
			i++;
		if (i != 0 && i != start)
		{
			aux = ft_substr(str, start, i - start);
			add_token(list, aux);
		}
		start = i;
		while (str[i] == '|' || str[i] == '<' || str[i] == '>')
			i++;
		if (i != start)
		{
			aux = ft_substr(str, start, i - start);
			add_token(list, aux);
		}
		start = i;
	}
}

void	lexer_split(char *line, t_token_list *list)
{
	int		i;
	int		start;
	bool	in_quote;
	char	quote_char;
	char	*token;

	i = 0;
	start = 0;
	in_quote = false;
	quote_char = '\0';
	while (line[i] != '\0')
	{
		if (is_quote(line[i]))
		{
			if (!in_quote)
			{
				in_quote = true;
				quote_char = line[i];
			}
			else if (line[i] == quote_char)
			{
				in_quote = false;
				quote_char = '\0';
			}
		}
		if ((line[i] == ' ' || line[i] == '\t') && !in_quote)
		{
			if (i > start)
			{
				token = ft_substr(line, start, i - start);
				add_token(list, token);
				free(token);
			}
			start = i + 1;
		}
		i++;
	}
	if (i > start)
	{
		token = ft_substr(line, start, i - start);
		add_token(list, token);
		free(token);
	}
}

t_error_code	lexer(char *input, t_list *envl)
{
	t_token_list	*list;

	if (!quotes_are_closed(input))
	{
		ft_putendl_fd("Error: mi bro no me ralles", 2);	
		return (2);
	}
	list = ft_calloc(1, sizeof(t_token_list));
	if (!list)
		return (MEM_ALLOC_ERROR);
	lexer_split(input, list);
	return (parser(list, envl));
}
