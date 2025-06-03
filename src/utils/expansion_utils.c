/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:01:42 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/06/03 11:23:34 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	replace_status_env(char **str, int last_status)
{
	int		replace_spot;
	char	*status_string;
	char	*final;

	replace_spot = ft_strnstr_iterator(*str, "$?", ft_strlen(*str));
	while (replace_spot != -1)
	{
		status_string = ft_itoa(last_status);
		final = replace_midstring(*str, "$?", status_string, replace_spot);
		free(status_string);
		status_string = 0;
		free(*str);
		*str = final;
		replace_spot = ft_strnstr_iterator(*str, "$?", ft_strlen(*str));
	}
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
		if (!*str)
			error_handler(EXIT_FAILURE);
		return ;
	}
	trimmed = ft_strtrim(env, " ");
	if (!trimmed)
		error_handler(EXIT_FAILURE);
	free(*str);
	*str = trimmed;
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
			replace_status_env((char **)&tmp->content, table->error_code);
		}
		delete_quotes((char *)tmp->content);
		tmp = tmp->next;
	}
	free(*token);
	*token = join_split_token(split_token);
	ft_lstclear(&split_token, free);
	table->error_code =NO_ERROR;
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
