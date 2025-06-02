/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:06:36 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/06/01 19:06:29 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_new_token_size(t_list *split_token)
{
	int		size;
	char	*token;

	size = 0;
	while (split_token)
	{
		token = split_token->content;
		size += ft_strlen(token);
		split_token = split_token->next;
	}
	return (size);
}

char	*join_split_token(t_list *split_token)
{
	char	*token;
	int		new_token_size;

	new_token_size = get_new_token_size(split_token);
	token = ft_calloc(new_token_size + 1, sizeof(char));
	if (!token)
		error_handler(EXIT_FAILURE);
	while (split_token)
	{
		ft_strcat(token, (char *)split_token->content);
		split_token = split_token->next;
	}
	ft_lstclear(&split_token, free);
	return (token);
}

int	is_token_empty(void *content)
{
	int		check;
	char	*token;

	token = content;
	if (*token == '\0')
		check = 1;
	else
		check = 0;
	return (check);
}

t_list	*get_split_token(char *token)
{
	t_list	*split_token;
	t_list	*new_node;
	char	*token_piece;
	int		curr_pos;
	int		saved_pos;

	split_token = 0;
	curr_pos = 0;
	saved_pos = 0;
	while (token[curr_pos])
	{
		saved_pos = curr_pos;
		if (is_quote(token[curr_pos]))
			skip_quotes((const char *)token, &curr_pos);
		else
			skip_letters((const char *)token, &curr_pos);
		token_piece = ft_substr(token, saved_pos, curr_pos - saved_pos);
		if (!token_piece)
			error_handler(EXIT_FAILURE);
		new_node = ft_lstnew((void *)token_piece);
		if (!new_node)
			error_handler(EXIT_FAILURE);
		ft_lstadd_back(&split_token, new_node);
	}
	return (split_token);
}
