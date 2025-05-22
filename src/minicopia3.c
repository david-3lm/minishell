/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicopia3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:02:41 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/22 15:06:44 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*saved;

	saved = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (saved);
}

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

char	*replace_midstring(char *original,
							char *old_substr,
							char *new_substr,
							int replace_i)
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

void	replace_vars_with_values(char **str, t_cmd_table *table)
{
	int		i;
	char	*var;
	char	*value;
	char	*final;

	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == '$' && !ft_strchr("? ", str[0][i + 1])
			&& str[0][i + 1] != '\0')
		{
			var = get_var_name(&str[0][i]);
			if (!mini_get_env(table, var + 1))
				return ;
			value = mini_get_env(table, var + 1)->value;
			final = replace_midstring(*str, var, value, i);
			free(*str);
			*str = final;
			free(var);
			i += ft_strlen(value) - 1;
			// if (value)
			// 	free(value);
		}
	}
}

void	replace_one_var(char **str, t_cmd_table *table)
{
	char	*env;
	char	*trimmed;

	if (!mini_get_env(table, *str + 1))
		return ;	
	env = mini_get_env(table, *str + 1)->value;
	if (!env)
	{
		free(*str);
		*str = ft_strdup("");
		// if (!*str)
		// 	quit_program(EXIT_FAILURE);
		return ;
	}
	trimmed = ft_strtrim(env, " ");
	// if (!trimmed)
	// 	quit_program(EXIT_FAILURE);
	//free(env);
	free(*str);
	*str = trimmed;
}

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

void	replace_status_env(char **str, int last_status)
{
	int		replace_spot;
	char	*status_string;
	char	*final;

	replace_spot = ft_strnstr_iterator(*str, "$?", ft_strlen(*str));
	while (replace_spot != -1)
	{
		status_string = ft_itoa(last_status);
		// if (status_string == 0)
		// 	return (quit_program(EXIT_FAILURE));
		final = replace_midstring(*str, "$?", status_string, replace_spot);
		free(status_string);
		status_string = 0;
		free(*str);
		*str = final;
		replace_spot = ft_strnstr_iterator(*str, "$?", ft_strlen(*str));
	}
}

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

void	skip_letters(const char *input, int *curr_pos)
{
	if (input[*curr_pos] == '$' || input[*curr_pos] == '/')
		(*curr_pos)++;
	while (input[*curr_pos] && !is_quote(input[*curr_pos])
		&& input[*curr_pos] != '$' && input[*curr_pos] != '/')
		(*curr_pos)++;
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

void	replace_env_single_token(char **token, t_cmd_table *table)
{
	t_list	*split_token;
	t_list	*tmp;
	char	*token_piece;

	split_token = get_split_token(*token);
	tmp = split_token;
	while (tmp)
	{
		token_piece = tmp->content;
		if (*token_piece != '\'')
		{
			if (*token_piece == '$' && ft_strcmp(token_piece, "$_") != 0
				&& ft_strcmp(token_piece, "$?") != 0 && *(token_piece + 1) != 0)
				replace_one_var((char **)&tmp->content, table);
			else
				replace_vars_with_values((char **)&tmp->content, table);
			replace_status_env((char **)&tmp->content, table->error_code); //CON NUESTRO ERROR CODE
		}
		delete_quotes((char *)tmp->content);
		tmp = tmp->next;
	}
	free(*token);
	*token = join_split_token(split_token);
	ft_lstclear(&split_token, free);
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

void	ft_lstdel_first(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	tmp = *lst;
	tmp = tmp->next;
	del((*lst)->content);
	free(*lst);
	*lst = tmp;
}

void	ft_lstclear_if(t_list **lst, int (*cmp)(void *), void (*del)(void *))
{
	if (!lst)
		return ;
	while (*lst)
	{
		if (cmp((*lst)->content))
			ft_lstdel_first(lst, del);
		else
			lst = &(*lst)->next;
	}
}

void	replace_envs(t_list **tokens, t_list *redirs, t_cmd_table *table)
{
	t_list	*token;
	t_redir	*redir;

	token = *tokens;
	while (token)
	{
		replace_env_single_token((char **)&token->content, table);
		token = token->next;
	}
	if (ft_lstsize(*tokens) > 1 && (char)*((char *)(*tokens)->content) != '\0')
		ft_lstclear_if(tokens, is_token_empty, free);
	while (redirs)
	{
		redir = redirs->content;
		replace_env_single_token(&redir->direction, table);
		redirs = redirs->next;
	}
}
