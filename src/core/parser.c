/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:03 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/30 17:02:45 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/// @brief Esta funcion devuelve la direccion de la redireccion
/// @param tok el token siguiente al que esta trabajando
/// @return char * de la direccion
char	*get_direction(t_tok *tok)
{
	if (!tok)
		return (NULL);
	if (tok->type != COMMAND && tok->type != STRING)
		return (NULL);
	return (tok->value);
}

/// @brief Da el tamaño del redir
/// @param value el string del redir
/// @return cuantos '<' o '>' tiene el redir
int	size_redir(char *value)
{
	int		i;
	char	redir;

	i = 0;
	redir = '\0';
	while (value[i])
	{
		if (!redir && (value[i] == '<' || value[i] == '>'))
		{
			if (value[i] == '<')
				redir = value[i];
			else if (value[i] == '>')
				redir = value[i];
		}
		i++;
	}
	if (count_char(value, '<') && count_char(value, '>'))
		return (-1);
	return (count_char(value, redir));
}

/// @brief Esta funcion crea un comando pero solo rellena redireccion
/// @param tok_list una referencia al token que contiene el <<, >>, ...
/// @return el comando creado
t_cmd	*add_redir(t_list *tok_list, t_cmd_table **table)
{
	t_redir	*redir;
	t_cmd	*cmd;
	t_tok	*tok;

	tok = (t_tok *)tok_list->content;
	if (!tok)
		return (NULL);
	cmd = alloc_cmd();
	redir = alloc_redir();
	if (!cmd || !redir)
		return (NULL);

	if (!set_redir_type(redir, tok->value, *table)
		|| !set_redir_direction(redir, tok_list, *table))
		return (NULL);

	attach_redir(cmd, redir, *table);
	return (cmd);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

char	*check_expansion(char *token, t_cmd_table *table, t_tok *tok)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	int		i;
	int		start;
	t_env	*env;
	t_list	*env_lst;

	i = 0;
	if (!tok->expand)
		return (ft_strdup(token));
	result = ft_calloc(1, sizeof(char));
	table->is_checker = false;
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			start = i;
			if (token[i] == '?')
			{
				table->is_checker = true;
				printf("anterior error code --> %d \n", table->error_code);
				return (NULL);
			}
			while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
				i++;
			var_name = ft_substr(token, start, i - start);
			var_value = NULL;
			env_lst = table->envv;
			while (env_lst)
			{
				env = (t_env *)env_lst->content;
				if (ft_strcmp(env->key, var_name) == 0)
				{
					var_value = env->value;
					break ;
				}
				env_lst = env_lst->next;
			}
			if (var_value)
				result = ft_strjoin_free(result, ft_strdup(var_value));
			else
				result = ft_strjoin_free(result, ft_strdup(""));
			free(var_name);
		}
		else
		{
			start = i;
			while (token[i] && token[i] != '$')
				i++;
			result = ft_strjoin_free(result,
					ft_substr(token, start, i - start));
		}
	}
	return (result);
}

void	add_cmds(t_token_list *tok, t_cmd_table **table)
{
	t_cmd	*current_cmd;
	t_list	*current_token;

	current_cmd = NULL;
	while (tok->tokens)
	{
		current_token = tok->tokens;
		if (!process_token(&current_cmd, current_token, table))
			return ;
		if (((t_tok *)(tok->tokens->content))->type == PIPE
			|| ((t_tok *)(tok->tokens->content))->type == REDIR)
			current_cmd = NULL;
		tok->tokens = tok->tokens->next;
	}
}

void	count_pipes(t_cmd_table *table)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	t_list	*token_list;
	t_tok	*tok;

	cmd_list = table->cmds;
	table->n_pipes = 0;
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		token_list = cmd->tokens;
		while (token_list)
		{
			tok = (t_tok *)token_list->content;
			if (tok->type == PIPE)
				table->n_pipes += 1;
			if (tok->type == PIPE_ERR)
				table->error_code = PIPE_ERROR;
			token_list = token_list->next;
		}
		cmd_list = cmd_list->next;
	}
}

void	clean_table(t_cmd_table *table)
{
	ft_lstclear(&(table->cmds), free);
	ft_lstclear(&(table->redirs), free);
	table->n_cmd = 0;
	table->n_pipes = 0;
}

t_error_code	parser(t_token_list *list, t_list *envl)
{
	static t_cmd_table	*table;

	if (!table)
		table = ft_calloc(1, sizeof(t_cmd_table));
	else
		clean_table(table);
	if (!table)
		return (MEM_ALLOC_ERROR);
	table->n_cmd = 0;
	table->envv = envl;
	add_cmds(list, &table);
	debug_parser(table); //borrar
	count_pipes(table);
	return (executor(table));
}
