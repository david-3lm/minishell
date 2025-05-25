/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:06:36 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/25 18:38:10 by dlopez-l         ###   ########.fr       */
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
	// if (!token)
	// 	quit_program(EXIT_FAILURE);
	while (split_token)
	{
		ft_strcat(token, (char *)split_token->content);
		split_token = split_token->next;
	}
	ft_lstclear(&split_token, free);
	return (token);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*var;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i] && !is_token_delimiter(str[i]) && str[i] != '$'
		&& str[i] != '=' && !is_quote(str[i]) && str[i] != '/')
		i++;
	var = ft_substr(str, 0, i);
	// if (!var)
	// 	quit_program(EXIT_FAILURE);
	return (var);
}

char	*replace_midstring(char *original, char *old_substr, char *new_substr, int replace_i)
{
	char	*final;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(original) - ft_strlen(old_substr) + ft_strlen(new_substr);
	final = ft_calloc(len + 1, sizeof(char));
	// if (final == 0)
	// 	quit_program(EXIT_FAILURE);
	while (*original)
	{
		if (i == replace_i)
		{
			while (new_substr && *new_substr)
			final[i++] = *(new_substr++);
			original += ft_strlen(old_substr);
			replace_i = -2;
		}
		if (*original)
			final[i++] = *(original++);
	}
	final[i] = '\0';
	return (final);
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
		// if (!token_piece)
		// 	quit_program(EXIT_FAILURE);
		new_node = ft_lstnew((void *)token_piece);
		// if (!new_node)
		// 	quit_program(EXIT_FAILURE);
		ft_lstadd_back(&split_token, new_node);
	}
	return (split_token);
}
