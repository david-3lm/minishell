/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:06:36 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/14 13:19:17 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_token(t_token_list *list, char *value)
{
	t_tok	*new_tok;

	new_tok = malloc(sizeof(t_tok));
	if (!new_tok)
		return ;
	new_tok->expand = value[0] != '\'';
	new_tok->type = get_ttype(value);
	if (new_tok->type == STRING && count_quotes(value) == 2)
	{
		new_tok->value = ft_substr(value, 1, ft_strlen(value) - 2);
	}
	else if (new_tok->type == STRING && count_quotes(value) != 2)
	{
		new_tok->value = ft_substr(value, 1, ft_strlen(value) - 2);
		return ;
	}
	else
		new_tok->value = ft_strdup(value);
	if (new_tok->type == PIPE && count_char(new_tok->value, '|') != 1)
	{
		error_handler(PIPE_ERROR);
		new_tok->type = PIPE_ERR;
	}
	ft_lstadd_back(&(list->tokens), ft_lstnew(new_tok));
}

void	update_quote_state(char c, bool *in_quote, char *quote_char)
{
	if (is_quote(c))
	{
		if (!(*in_quote))
		{
			*in_quote = true;
			*quote_char = c;
		}
		else if (c == *quote_char)
		{
			*in_quote = false;
			*quote_char = '\0';
		}
	}
}

void	handle_token_segment(char *line, t_token_list *list, int *start, int i)
{
	char	*token;

	if (i > *start)
	{
		token = ft_substr(line, *start, i - *start);
		printf("TOKEN => %s\n", token);
		add_token(list, token);
		free(token);
	}
	if (line[i] == '<' || line[i] == '>')
	{
		*start = i;
		if (line[i+1] == line[i])
		{
			handle_last_token(line, list, *start, i + 2);
			*start = i + 2;
		}
		else
		{
			handle_last_token(line, list, *start, i + 1);
			*start = i + 1;
		}
	}
	else
		*start = i + 1;
}

void	handle_last_token(char *line, t_token_list *list, int start, int end)
{
	char	*token;

	if (end > start)
	{
		token = ft_substr(line, start, end - start);
		printf("TOKEN LAST => %s\n", token);
		add_token(list, token);
		free(token);
	}
}
