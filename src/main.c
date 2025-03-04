/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:27 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/02/28 02:11:17 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

const char	*get_type_name(t_tok_type type)
{
	if (type == COMMAND)
		return "COMMAND";
	if (type == STRING)
		return "STRING";
	if (type == FILES)
		return "FILE";
	if (type == REDIR)
		return "REDIR";
	if (type == PIPE)
		return "PIPE";
	if (type == VARIABLE)
		return "VARIABLE";
	return "UNKNOWN";
}

void	debug(t_token_list *list)
{
	t_list	*node;

	node = list->tokens;
	while (node->next != NULL)
	{
		ft_printf(YELLOW "%s => %s %s \n", get_type_name(((t_tok *)node->content)->type), ((t_tok *)node->content)->value, RESET_COLOR);
		node = node->next;
	}
	ft_printf(YELLOW "%s => %s %s \n", get_type_name(((t_tok *) node->content)->type), ((t_tok *) node->content)->value, RESET_COLOR);

}

int	main(void)
{
	struct sigaction	s_sigaction;
	char				*rl;
	t_error_code		code;

	s_sigaction.sa_sigaction = handle_signal;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sigaction.sa_mask);
	sigaction(SIGINT, &s_sigaction, 0);
	rl = readline("\033[1;32m🌋 Kontxesi ↝ \033[0m");
	while (true)
	{
		add_history(rl);
		code = lexer(rl);
		ft_printf(YELLOW "main => %d %s\n", code, RESET_COLOR);
		if (code != NO_ERROR)
			return (1);
		rl = readline("\033[1;32m🌋 Kontxesi ↝ \033[0m");
		if (rl == NULL)
		{
			ft_printf("Ta luego (mensaje que seguro hace reir a carol) 🎷🦆");
			return (1);
		}
	}
	return (0);
}
