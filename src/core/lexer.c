/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:08 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/14 13:25:33 by dlopez-l         ###   ########.fr       */
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
		while (str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] && str[i] != ' ')
			i++;
		if (i != 0 && i != start)
		{
			aux = ft_substr(str, start, i - start);
			add_token(list, aux);
		}
		start = i;
		while ((str[i] == '<' || str[i] == '>') && str[i + 1] == str[i])
			i += 2;
		while (str[i] == '<' || str[i] == '>' || str[i] == '|')
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

	i = 0;
	start = 0;
	in_quote = false;
	quote_char = '\0';
	while (line[i] != '\0')
	{
		update_quote_state(line[i], &in_quote, &quote_char);
		if (is_separator(line[i]) && !in_quote)
			handle_token_segment(line, list, &start, i);
		if(line[i] == '>' && line[i + 1] == line[i])
			i += 2;
		else
			i++;
		ft_printf("POST +I => %c\n", line[i]);
	}
	handle_last_token(line, list, start, i);
}

t_error_code	lexer(char *input, t_list **envl)
{
	t_token_list	*list;

	signal(SIGINT, handle_interact);
	signal(SIGQUIT, handle_interact);
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
