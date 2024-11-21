/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:03 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/21 13:17:17 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_cmds(t_token_list *tok, t_cmd_table **table)
{
	t_cmd	*new_cmd;
	t_list	*current_token;
	t_list	*new_token_node;
	t_tok	*token_content;

	while (tok->tokens != NULL)
	{
		// Crear un nuevo comando
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			return ;
		new_cmd->tokens = NULL; // Inicializar la lista de tokens del comando
		new_cmd->redirs = NULL; // Inicializar redirecciones

		// Iterar sobre los tokens para duplicarlos
		current_token = tok->tokens;
		while (current_token)
		{
			token_content = (t_tok *)current_token->content;
			if (!token_content)
				break;

			// Crear un nuevo token duplicado
			t_tok *new_token = malloc(sizeof(t_tok));
			if (!new_token)
				return ;
			new_token->type = token_content->type;
			new_token->value = strdup(token_content->value); // Duplica el valor del token
			new_token_node = ft_lstnew(new_token);
			ft_lstadd_back(&(new_cmd->tokens), new_token_node);

			current_token = current_token->next;
		}

		// Agregar el nuevo comando a la tabla
		ft_lstadd_back(&(*table)->cmds, ft_lstnew(new_cmd));
		(*table)->n_cmd += 1;

		// Avanzar al siguiente token en la lista principal
		tok->tokens = tok->tokens->next;
	}
}


t_cmd_table	*parser(t_token_list *list)
{
	t_cmd_table *table;

	// Inicializar la tabla de comandos
	table = ft_calloc(1, sizeof(t_cmd_table));
	if (!table)
		return (NULL);
	table->n_cmd = 0;

	// Añadir comandos a la tabla
	add_cmds(list, &table);

	// Verificar e imprimir los tokens del primer comando
	if (table->cmds && table->cmds->content)
	{
		t_cmd *first_cmd = (t_cmd *)table->cmds->content;
		t_list *token_list = first_cmd->tokens;
		while (token_list)
		{
			t_tok *token = (t_tok *)token_list->content;
			if (token && token->value)
				ft_printf("Token: %s\n", token->value);
			token_list = token_list->next;
		}
	}
	return (table);
}
