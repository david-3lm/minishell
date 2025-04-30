/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:27 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/30 16:00:51 by dlopez-l         ###   ########.fr       */
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
			ft_printf("Gora Kontxesi 🎷🦆\n");
			break ;
		}
		if (*rl)
			add_history(rl);
		lexer(rl, envl);
		free(rl);
	}
	return (0);
}
