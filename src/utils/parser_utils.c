/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:01:41 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/25 18:31:29 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	delete_quotes(char *token)
{
	int	i;
	int	has_double_quotes_open;
	int	has_single_quotes_open;

	i = 0;
	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	while (token[i])
	{
		if (token[i] == '"' && has_single_quotes_open == 0)
		{
			has_double_quotes_open = !has_double_quotes_open;
			ft_strcpy(&token[i], (const char *)&token[i + 1]);
			continue ;
		}
		else if (token[i] == '\'' && has_double_quotes_open == 0)
		{
			has_single_quotes_open = !has_single_quotes_open;
			ft_strcpy(&token[i], (const char *)&token[i + 1]);
			continue ;
		}
		i++;
	}
}

void	concat(char *dest, char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		ft_strcat(dest, strs[i]);
		i++;
	}
}

char	*ft_strstr_quotes(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (!(*to_find))
		return (str);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			skip_quotes(str, &i);
		if (!ft_strncmp(&str[i], to_find, ft_strlen(to_find)))
			return (&str[i]);
		if (str[i])
			i++;
	}
	return (0);
}

int	is_input_valid_unexpected_token(const char *input, char *err_message)
{
	int		check;

	if (has_quotes_open(input, err_message)
		|| has_char_at_beginning(input, '|', err_message)
		|| has_char_at_beginning(input, ';', err_message)
		|| has_char_at_end(input, '|', err_message)
		|| has_char_at_end(input, '<', err_message)
		|| has_char_at_end(input, '>', err_message)
		|| has_char_at_end(input, '&', err_message)
		|| has_forbidden_sequence(input, ";;", err_message)
		|| has_forbidden_sequence(input, "|;", err_message)
		|| has_forbidden_sequence(input, "&;", err_message)
		|| has_forbidden_sequence(input, ";|", err_message)
		|| has_forbidden_sequence(input, ";&", err_message)
		|| has_forbidden_sequence(input, ">>>", err_message)
		|| has_spaces_between_char(input, '|', err_message)
		|| has_spaces_between_char(input, '>', err_message))
		check = 0;
	else
		check = 1;
	return (check);
}

int	is_input_valid_not_supported(const char *input, char *err_message)
{
	int		check;

	if (has_non_supported(input, "*", err_message)
		|| has_non_supported(input, "\\", err_message)
		|| has_non_supported_one(input, "&", err_message))
		check = 0;
	else
		check = 1;
	return (check);
}
