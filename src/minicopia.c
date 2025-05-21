/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicopia.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:18:54 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/21 15:30:52 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (9 <= c && c <= 13));
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

void	free_arr(void **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

int	ft_strisspace(char *str)
{
	int	check;

	if (!str || !(*str))
		return (0);
	check = 1;
	while (*str)
	{
		if (!ft_isspace(*str))
		{
			check = 0;
			break ;
		}
		str++;
	}
	return (check);
}

size_t	get_length(char **strs)
{
	size_t	len;

	len = 0;
	while (*strs)
	{
		len += ft_strlen(*strs);
		strs++;
	}
	return (len);
}

char	*ft_strtrim_all(const char *s1, const char *set)
{
	char	*new_str;
	char	**split;
	size_t	size_new_str;

	if (!s1)
		return (0);
	split = ft_split_set((char *)s1, (char *)set);
	if (!split)
		return (0);
	size_new_str = get_length(split);
	if (size_new_str == 0)
		return (ft_strdup(""));
	new_str = ft_calloc(size_new_str + 1, sizeof(char));
	if (!new_str)
		return (0);
	concat(new_str, split);
	free_arr((void **)split);
	return (new_str);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*saved;

	saved = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (saved);
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

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	char	*sav_d;

	sav_d = dest;
	while (*dest)
		dest++;
	while (nb && *src)
	{
		*dest++ = *src++;
		nb--;
	}
	*dest = '\0';
	return (sav_d);
}

int	has_char_at_beginning(const char *input, char c, char *err_message)
{
	int		check;
	char	*cpy;

	cpy = ft_strtrim(input, WHITE_SPACE);
	//if (!cpy)
		//quit_program(EXIT_FAILURE);
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
	//if (!cpy)
		//quit_program(EXIT_FAILURE);
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


int	is_input_valid(const char *input)
{
	int		check;
	char	err_message[100];

	ft_bzero(err_message, 0);
	if (*input == '\0' || ft_strisspace((char *)input))
		check = 0;
	else if (!is_input_valid_unexpected_token(input, err_message)
		|| !is_input_valid_not_supported(input, err_message))
	{
		check = 0;
		// g_msh.exit_status = 8; //ERROR CODE
		//write_msh_error(err_message);
	}
	else
		check = 1;
	return (check);
}
