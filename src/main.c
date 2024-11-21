/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:27 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/21 13:19:05 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

const char *get_type_name(t_tok_type type)
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
	t_list *node;

	node = list->tokens;
	while (node->next != NULL)
	{
		ft_printf("%s => %s\n", get_type_name(((t_tok *)node->content)->type), ((t_tok *)node->content)->value);
		node = node->next;
	}
	ft_printf("%s => %s\n", get_type_name(((t_tok *) node->content)->type), ((t_tok *) node->content)->value);

}

int	main(void)
{
	char	*rl;
	t_token_list *l;

	rl = readline("\033[1;32m🎅 Concepción ↝ \033[0m");
	while (rl != NULL)
	{
		l = lexer(rl);
		//debug(l);
		(void) l;
		rl = readline("\033[1;32m🎅 Concepción ↝ \033[0m");
	}
	return (0);
}
