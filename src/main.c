/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:27 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/22 15:40:41 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	ft_printf(MAGENTA " === Command Table Debug ===\n");
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

const char	*get_type_name(t_tok_type type)
{
	if (type == COMMAND)
		return ("COMMAND");
	if (type == STRING)
		return ("STRING");
	if (type == FILES)
		return ("FILE");
	if (type == REDIR)
		return ("REDIR");
	if (type == PIPE)
		return ("PIPE");
	if (type == VARIABLE)
		return ("VARIABLE");
	return ("UNKNOWN");
}

#include <stdio.h>

void	print_tokens(t_list *tokens)
{
	int i = 0;
	while (tokens)
	{
		char *token = (char *)tokens->content;
		printf("      Token %d: %s\n", i++, token);
		tokens = tokens->next;
	}
}

void	print_redirs(t_list *redirs)
{
	int i = 0;
	while (redirs)
	{
		t_redir *redir = (t_redir *)redirs->content;
		printf("      Redir %d: type='%d', direction='%s'\n", i++, redir->type, redir->direction);
		redirs = redirs->next;
	}
}

void	debug_table(t_cmd_table *table)
{
	if (!table)
	{
		printf("Table is NULL\n");
		return;
	}
	printf("Debugging Command Table:\n");
	printf("  Number of commands: %d\n", table->n_cmd);

	t_list *cmd_node = table->cmds;
	int cmd_index = 0;
	while (cmd_node)
	{
		t_cmd *cmd = (t_cmd *)cmd_node->content;
		printf("  Command %d:\n", cmd_index);

		if (cmd->tokens)
			print_tokens(cmd->tokens);
		else
			printf("    No tokens\n");

		if (cmd->redirs)
			print_redirs(cmd->redirs);
		else
			printf("    No redirections\n");

		cmd_node = cmd_node->next;
		cmd_index++;
	}
}


//TODO: HEREDOC

int	main(int argc, char **argv, char **envp)
{
	char				*rl;
	t_list				*envl;
	t_cmd_table			*table;
	int					curr_pos;
	int					err_code;

	err_code = 0;
	if (is_inside_kntxesi(argc, argv))
		envl = env_init(envp, argv[1]);
	else
		envl = env_init(envp, NULL);
	g_heredoc = 1;
	while (1)
	{
		curr_pos = 0;
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		rl = readline("\001\033[1;32m\002🌋 Kontxesi ↝ \001\033[0m\002");
		if (!rl)
		{
			ft_printf("Gora Kontxesi 🎷🦆\n");
			break ;
		}
		if (*rl)
			add_history(rl);
		// lexer(rl, &envl);

		// MINICOPIA
		if (!is_input_valid(rl))
			continue ;
		table = get_cmd_table(rl, &curr_pos);
		if (!table->envv)
			table->envv = &envl;
		table->error_code = err_code;
		executor(table);
		err_code = table->error_code;
		free_cmd_table(table);
		free(table);
		free(rl);
	}
	free_env(envl);
	return (0);
}
