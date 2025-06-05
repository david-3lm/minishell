/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:27 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/06/05 13:08:36 by cde-migu         ###   ########.fr       */
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

void	exec_table(t_cmd_table *table, t_list *envl, int err_code)
{
	if (!table->envv)
		table->envv = &envl;
	table->error_code = err_code;
	executor(table);
}

void	main_loop(t_cmd_table *table, int err_code, t_list *envl)
{
	int		curr_pos;
	char	*rl;

	while (1)
	{
		curr_pos = 0;
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		rl = readline("\001\033[1;32m\002🐉 Kontxesi ↝ \001\033[0m\002");
		if (!rl)
		{
			ft_printf("Gora Kontxesi 🎷🦆\n");
			return ;
		}
		if (*rl)
			add_history(rl);
		if (!is_input_valid(rl))
			continue ;
		table = get_cmd_table(rl, &curr_pos);
		exec_table(table, envl, err_code);
		free(rl);
		err_code = table->error_code;
		free_cmd_table(table);
		free(table);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			err_code;
	t_list		*envl;
	t_cmd_table	*table;

	err_code = 0;
	printf(KONTXESI"\n");
	if (is_inside_kntxesi(argc, argv))
		envl = env_init(envp, argv[1]);
	else
		envl = env_init(envp, NULL);
	g_heredoc = 1;
	table = NULL;
	main_loop(table, err_code, envl);
	free_env(envl);
	return (0);
}
