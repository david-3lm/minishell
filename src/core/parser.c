/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:03 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/25 19:30:47 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*get_token(const char *input, int *curr_pos)
{
	char	*token;
	int		saved_pos;

	saved_pos = *curr_pos;
	while (input[*curr_pos] && !is_token_delimiter(input[*curr_pos]))
	{
		if (is_quote(input[*curr_pos]))
			skip_quotes(input, curr_pos);
		else if (input[*curr_pos])
			(*curr_pos)++;
	}
	token = ft_substr(input, saved_pos, *curr_pos - saved_pos);
	// if (!token)
		// quit_program(EXIT_FAILURE);
	printf("TOKEN  => %s\n", token);
	return (token);
}

t_redir	*get_redir(const char *input, int *curr_pos)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	// if (!redir)
		// quit_program(EXIT_FAILURE);
	if (!ft_strncmp(&input[*curr_pos], "<<", 2))
	{
		// ft_strncpy((char *)redir->type, (char *)&input[*curr_pos], 2);
		redir->type = RD_HD;
		*curr_pos += 2;
	}
	else if (input[*curr_pos] == '<')
	{
		redir->type = RD_SIN;
		(*curr_pos)++;
	}
	else if (!ft_strncmp(&input[*curr_pos], ">>", 2))
	{
		redir->type = RD_SOUT2;
		*curr_pos += 2;
	}
	else if (input[*curr_pos] == '>')
	{
		redir->type = RD_SOUT;
		(*curr_pos)++;
	}
	skip_spaces(input, curr_pos);
	redir->direction = get_token(input, curr_pos);
	return (redir);
}

t_cmd	*get_cmds(const char *input, int *curr_pos)
{
	t_cmd	*cmd;
	t_list	*new_node;

	cmd = ft_calloc(1, sizeof(t_cmd));
	// if (!cmd)
		// quit_program(EXIT_FAILURE);
	while (input[*curr_pos] && !is_cmd_delimiter(input[*curr_pos]))
	{
		if (input[*curr_pos] != '>' && input[*curr_pos] != '<')
		{
			new_node = ft_lstnew((void *)get_token(input, curr_pos));
			// if (!new_node)
			// quit_program(EXIT_FAILURE);
			ft_lstadd_back(&cmd->tokens, new_node);
		}
		else if (input[*curr_pos] == '>' || input[*curr_pos] == '<')
		{
			if (ft_lstsize(cmd->tokens) == 0)
			{
				printf("entro aqi %c\n", input[*curr_pos]);
				new_node = ft_lstnew((void *)get_token(input, curr_pos));
				// if (!new_node)
				// quit_program(EXIT_FAILURE);
				ft_lstadd_back(&cmd->tokens, new_node);
			}
			new_node = ft_lstnew((void *)get_redir(input, curr_pos));
			// if (!new_node)
				// quit_program(EXIT_FAILURE);
			ft_lstadd_back(&cmd->redirs, new_node);
		}
		skip_spaces(input, curr_pos);
	}
	return (cmd);
}

t_cmd_table	*get_cmd_table(const char *input, int *curr_pos)
{
	t_cmd_table	*cmd_table;
	t_list		*cmd;

	cmd_table = ft_calloc(1, sizeof(t_cmd_table));
	// if (!cmd_table)
		// quit_program(EXIT_FAILURE);
	while (input[*curr_pos])
	{
		skip_spaces(input, curr_pos);
		cmd = ft_lstnew((void *)get_cmds(input, curr_pos));
		// if (!cmd)
			// quit_program(EXIT_FAILURE);
		ft_lstadd_back(&cmd_table->cmds, cmd);
		if (input[*curr_pos] == '|' && input[*curr_pos + 1] != '|')
			(*curr_pos)++;
	}
	return (cmd_table);
}
