/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:14:32 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/06/01 19:10:31 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_char_at_beginning(const char *input, char c, char *err_message)
{
	int		check;
	char	*cpy;

	cpy = ft_strtrim(input, WHITE_SPACE);
	if (!cpy)
		error_handler(EXIT_FAILURE);
	if (cpy[0] == c)
	{
		check = 1;
		ft_strcpy(err_message, "syntax error near unexpected token `");
		ft_strncat(err_message, &c, 1);
		ft_strncat(err_message, "'", 2);
	}
	else
		check = 0;
	free(cpy);
	return (check);
}

int	has_char_at_end(const char *input, char c, char *err_message)
{
	int		check;
	char	*cpy;
	int		len;

	cpy = ft_strtrim(input, WHITE_SPACE);
	if (!cpy)
		error_handler(EXIT_FAILURE);
	len = ft_strlen(cpy);
	if (cpy[len - 1] == c)
	{
		check = 1;
		ft_strcpy(err_message, "syntax error near unexpected token `");
		ft_strncat(err_message, &c, 1);
		ft_strncat(err_message, "'", 2);
	}
	else
		check = 0;
	free(cpy);
	return (check);
}

int	has_spaces_between_char(const char *input, char c, char *err_message)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			skip_quotes(input, &i);
		if (input[i] == c && input[i + 1] == ' ')
		{
			i++;
			skip_spaces((char *)input, &i);
			if (input[i] == c)
			{
				ft_strcpy(err_message, "syntax error near unexpected token `");
				ft_strncat(err_message, &c, 1);
				ft_strcat(err_message, "'");
				return (1);
			}
		}
		if (input[i])
			i++;
	}
	return (0);
}
