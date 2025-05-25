/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:35:13 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/25 18:53:41 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strnstr_iterator(char *haystack, char *needle, size_t len)
{
	size_t	little_len;
	int		iterator;

	iterator = 0;
	little_len = ft_strlen(needle);
	if (little_len == 0)
		return (-1);
	if (len == 0)
		return (-1);
	while (haystack[iterator] && (int)(little_len <= len - iterator))
	{
		if (!ft_strncmp(&haystack[iterator], (char *)needle, little_len))
			return (iterator);
		iterator++;
	}
	return (-1);
}

void	skip_letters(const char *input, int *curr_pos)
{
	if (input[*curr_pos] == '$' || input[*curr_pos] == '/')
		(*curr_pos)++;
	while (input[*curr_pos] && !is_quote(input[*curr_pos])
		&& input[*curr_pos] != '$' && input[*curr_pos] != '/')
		(*curr_pos)++;
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
