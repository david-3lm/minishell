/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:27 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/29 18:12:52 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	debug(t_token_list *list)
{
	t_list	*node;

	node = list->tokens;
	// TODO: eliminar esta funcion y donde se la llama
	while (node->next != NULL)
	{
		printf(PINK "%s => %s %s \n", get_type_name(((t_tok *)node->content)->type), ((t_tok *)node->content)->value, RESET_COLOR);
		node = node->next;
	}
	ft_printf(PINK "%s => %s %s \n", get_type_name(((t_tok *) node->content)->type), ((t_tok *) node->content)->value, RESET_COLOR);

}

int	main(int argc, char **argv, char **envp)
{
	char				*rl;
	t_error_code		code;
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
			ft_printf("Gora Kontxesi 🎷🦆\n");
			break ;
		}
		if (*rl) // solo guarda en el historial si hay algo escrito
			add_history(rl);
		code = lexer(rl, envl);
		free(rl);
		ft_printf(PINK "main => %d\n" RESET_COLOR, code);
	}
	return (0);
}
