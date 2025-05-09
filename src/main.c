/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:27 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/09 12:39:18 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* void	debug_parser(t_cmd_table *table)
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
} */

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

//TODO: liberar los distintos tipos de t_list *
int	main(int argc, char **argv, char **envp)
{
	char				*rl;
	t_list				*envl;

	(void)argc;
	(void)argv;
	envl = env_init(envp);
	g_heredoc = 1;
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		rl = readline("\001\033[1;32m\002🌋 Kontxesi ↝ \001\033[0m\002");
		if (!rl)
		{
			ft_printf("Gora Jakobo 🎷🦆\n");
			break ;
		}
		if (*rl)
			add_history(rl);
		lexer(rl, &envl);
		free(rl);
	}
	free_env(envl);
	return (0);
}
