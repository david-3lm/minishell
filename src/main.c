/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:27 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/24 12:19:27 by cde-migu         ###   ########.fr       */
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
	while (node->next != NULL)
	{
		printf(PINK "%s => %s %s \n", get_type_name(((t_tok *)node->content)->type), ((t_tok *)node->content)->value, RESET_COLOR);
		node = node->next;
	}
	ft_printf(PINK "%s => %s %s \n", get_type_name(((t_tok *) node->content)->type), ((t_tok *) node->content)->value, RESET_COLOR);

}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	s_sigaction;
	char				*rl;
	t_error_code		code;
	t_list				*envl;
	
	(void)argc;
	(void)argv;
	s_sigaction.sa_sigaction = handle_signal;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sigaction.sa_mask);
	sigaction(SIGINT, &s_sigaction, 0);
	signal(SIGQUIT, SIG_IGN);
	envl = env_init(envp);
	rl = readline("\033[1;32m🌋 Kontxesi ↝ \033[0m");
	while (rl != NULL)
	{
		add_history(rl);
		code = lexer(rl, envl);
		ft_printf(PINK "main => %d %s\n", code, RESET_COLOR);
		if (code != NO_ERROR)
			return (1);
		rl = readline("\033[1;32m🌋 Kontxesi ↝ \033[0m"); 
		if (rl == NULL)
		{
			ft_printf("Gora Kontxesi 🎷🦆");
			return (1);
		}
	}
	return (0);
}
