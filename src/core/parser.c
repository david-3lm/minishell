/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:03 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/24 19:52:27 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	debug_parser(t_cmd_table *table)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	t_list	*token_list;
	t_tok	*token;
	int		cmd_index;

	if (!table || !table->cmds)
	{
		ft_printf("No commands found in the table.\n");
		return ;
	}

	cmd_list = table->cmds;
	cmd_index = 0;
	ft_printf(PINK " === Command Table Debug ===\n");
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		ft_printf("Command %d:\n", cmd_index);
		if (cmd && cmd->tokens)
		{
			token_list = cmd->tokens;
			while (token_list)
			{
				token = (t_tok *)token_list->content;
				if (token && token->value)
					ft_printf(" Token: [Type: %d, Value: '%s']\n", token->type, token->value);
				if (token->type == REDIR)
					ft_printf("  Redir: [Type: %d, Direction: '%s']\n", ((t_redir *)cmd->redirs->content)->type, ((t_redir *)cmd->redirs->content)->direction);
				token_list = token_list->next;
			}
		}
		else
		{
			ft_printf("  No tokens found for this command.\n");
		}
		cmd_list = cmd_list->next;
		cmd_index++;
	}
	ft_printf("========================== \n" RESET_COLOR);
}

/// @brief Esta funcion devuelve la direccion de la redireccion
/// @param tok el token siguiente al que esta trabajando
/// @return char * de la direccion
char	*get_direction(t_tok *tok)
{
	if (!tok)
		return NULL; //OJJO DEVOLVER ERRORES SI NO TIENE DIRECCION?
	printf(PINK "DIRECCION DEL TOK => %s CON TIPO %d %s \n", (tok->value), tok->type, RESET_COLOR);
	if (tok->type != COMMAND && tok->type != STRING)
		return NULL;
	return (tok->value);
}
/// @brief Da el tamaño del redir
/// @param value el string del redir
/// @return cuantos '<' o '>' tiene el redir
int		size_redir(char *value)
{
	int		i;
	int		count;
	char	redir;
	char	wrong;

	i = 0;
	count = 0;
	while (value[i])
	{
		if (!redir && (value[i] == '<' || value[i] == '>'))
		{
			if (value[i] == '<')
			{
				redir = value[i];
				wrong = '>';
			}
			else if (value[i] == '>')
			{
				wrong = '<';
				redir = value[i];
			}
		}
		if (value[i] == redir)
			count++;
		if (value[i] == wrong)
			return (-1);
		i++;
	}
	return (count);
}

/// @brief Esta funcion crea un comando pero solo rellena redireccion
/// @param tok_list una referencia al token que contiene el <<, >>, ...
/// @return el comando creado
t_cmd	*add_redir(t_list *tok_list, t_cmd_table **table)
{
	t_tok	*tok;
	t_redir	*redir;
	t_cmd	*cmd;

	tok = (t_tok *)tok_list->content;
	redir = malloc(sizeof(t_redir));
	cmd = malloc(sizeof(t_cmd));
	if (!redir || !cmd || !tok)
		return (NULL);
	if (size_redir(tok->value) == 2)
	{
		if (ft_strncmp(tok->value, ">>", 2) == 0)
			redir->type = RD_SOUT2;
		else if (ft_strncmp(tok->value, "<<", 2) == 0)
			redir->type = RD_HD;
	}
	else if (size_redir(tok->value) == 1)
	{
		if (ft_strncmp(tok->value, ">", 1) == 0)
			redir->type = RD_SOUT;
		else if (ft_strncmp(tok->value, "<", 1) == 0)
			redir->type = RD_SIN;
	}
	else
	{
		ft_printf(PINK "TERRIBLE REDIR\n" RESET_COLOR);
		free(redir);
		error_handler(REDIR_ERROR);
		(*table)->error_code = REDIR_ERROR;
		return (NULL);
	}
	if (tok_list->next)
	{
		redir->direction = get_direction((t_tok *)tok_list->next->content);
		printf(PINK "DIRECCION DEL REDIR => %s %s\n", (redir->direction), RESET_COLOR);
		if (!redir->direction)
		{
			free(redir);
			error_handler(REDIR_ERROR);
			(*table)->error_code = REDIR_ERROR;
			return (NULL);
		}
	}
	else
	{
		ft_printf("Error: falta la dirección de la redirección\n"); //TODO AÑADIR GESTION DE ERRORES AQUI
		return (NULL);
	}
	ft_lstadd_back(&cmd->redirs, ft_lstnew(redir));
	ft_lstadd_back(&(*table)->redirs, ft_lstnew(redir));
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
	int		i = 0;
	int		start;
	t_env	*env;
	t_list	*env_lst;

	if (!tok->expand)
		return (ft_strdup(token));
	result = ft_calloc(1, sizeof(char));
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			start = i;
			if (token[i] == '?')
			{
				printf("anterior error code --> %d \n", table->error_code);
				return (ft_itoa(table->error_code));
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
					break;
				}
				env_lst = env_lst->next;
			}
			result = ft_strjoin_free(result, ft_strdup(var_value ? var_value : ""));
			free(var_name);
		}
		else
		{
			start = i;
			while (token[i] && token[i] != '$')
				i++;
			result = ft_strjoin_free(result, ft_substr(token, start, i - start));
		}
	}
	return (result);
}

void	add_cmds(t_token_list *tok, t_cmd_table **table)
{
	t_cmd	*current_cmd = NULL;
	t_list	*current_token;
	t_tok	*token_content;
	t_tok	*new_token;

	while (tok->tokens != NULL)
	{
		current_token = tok->tokens;
		token_content = (t_tok *)current_token->content;
		if (!token_content)
			break ;
		if (current_cmd == NULL || (token_content->type != COMMAND && token_content->type != STRING))
		{
			if (token_content->type == REDIR)
			{
				current_cmd = add_redir(current_token, table);
				if (!current_cmd)
					error_handler(WRONG_CMD_ERROR);
			}
			else
			{
				current_cmd = malloc(sizeof(t_cmd));
				current_cmd->tokens = NULL;
				current_cmd->redirs = NULL;
				current_cmd->builtin = builtin_arr(token_content->value);
			}
			if (!current_cmd)
				return ;
			ft_lstadd_back(&(*table)->cmds, ft_lstnew(current_cmd));
			(*table)->n_cmd += 1;
		}
		new_token = malloc(sizeof(t_tok));
		if (!new_token)
			return ;
		new_token->type = token_content->type;
		new_token->value = check_expansion(token_content->value, *table, token_content);
		ft_lstadd_back(&(current_cmd->tokens), ft_lstnew(new_token));
		if (token_content->type == PIPE || token_content->type == REDIR)
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

t_error_code	parser(t_token_list *list, t_list *envl)
{
	t_cmd_table	*table;

	table = ft_calloc(1, sizeof(t_cmd_table));
	if (!table)
		return (MEM_ALLOC_ERROR);
	table->n_cmd = 0;
	table->envv = envl;
	add_cmds(list, &table);
	debug_parser(table); //borrar
	count_pipes(table);
	if (table->error_code != NO_ERROR)
		return (table->error_code);
	table->error_code = NO_ERROR;
	return (executor(table));
}
