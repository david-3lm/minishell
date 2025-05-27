/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:16:21 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/25 18:20:50 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_forbidden_sequence(const char *input, char *test, char *err_message)
{
	int		check;
	char	*trimmed;

	trimmed = ft_strtrim_all(input, WHITE_SPACE);
	//if (!trimmed)
		//quit_program(EXIT_FAILURE);
	if (ft_strstr_quotes(trimmed, test) != 0)
	{
		check = 1;
		ft_strcpy(err_message, "syntax error near unexpected token `");
		ft_strncat(err_message, test, 1);
		ft_strcat(err_message, "'");
	}
	else
		check = 0;
	free(trimmed);
	return (check);
}


int	has_non_supported(const char *input, char *test, char *err_message)
{
	int		check;

	if (ft_strstr_quotes((char *)input, test) != 0)
	{
		check = 1;
		ft_strcpy(err_message, "\"");
		ft_strcat(err_message, test);
		ft_strcat(err_message, "\" not supported");
	}
	else
		check = 0;
	return (check);
}

int	has_non_supported_one(const char *input, char *test, char *err_message)
{
	int		check;
	char	*tmp;

	check = 0;
	tmp = (char *)input;
	while (tmp)
	{
		tmp = ft_strstr_quotes(tmp, test);
		if (tmp != 0 && *(tmp + 1) != *test)
		{
			check = 1;
			break ;
		}
		else if (tmp != 0 && *(tmp + 1) == *test)
			tmp += 2;
	}
	if (check)
	{
		ft_strcpy(err_message, "\"");
		ft_strcat(err_message, test);
		ft_strcat(err_message, "\" not supported");
	}
	return (check);
}

int	has_quotes_open(const char *input, char *err_message)
{
	int	check;
	int	has_dquotes_open;
	int	has_squotes_open;

	check = 1;
	has_dquotes_open = 0;
	has_squotes_open = 0;
	while (*input)
	{
		if (*input == '"' && has_squotes_open == 0)
			has_dquotes_open = !has_dquotes_open;
		else if (*input == '\'' && has_dquotes_open == 0)
			has_squotes_open = !has_squotes_open;
		input++;
	}
	if (has_dquotes_open || has_squotes_open)
	{
		check = 1;
		ft_strcpy(err_message, "syntax error: open quotes");
	}
	else
		check = 0;
	return (check);
}
