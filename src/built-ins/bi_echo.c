/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/25 14:56:18 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
	- si es solo echo sin argumento, salto de linea
	- una variable para comprobar si tiene o no -n
 */
void	print_lines(t_list *tok, int out, bool n_opt)
{
	char	*str;

	while (tok)
	{
		str = ((t_tok *)tok->content)->value;
		if (str)
			ft_putstr_fd(str, out);
		tok = tok->next;
	}
	if (n_opt == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
}


int	bi_echo(t_cmd_table *table, t_cmd *cmd)
{
	t_list	*next;
	char	*aux;
	int		i;
	bool	n_opt;

	(void)table;
	n_opt = false;
	next = cmd->tokens->next;
	aux = (char *)((t_tok *)next->content)->value;
	i = 0;
	if (aux[i] && aux[i] == '-' && aux[i + 1] == 'n')
	{
		i++;
		while (aux[i] == 'n')
			i++;
		if (aux[i] == '\0')
		{
			n_opt = true;
			next = next->next;
		}
	}
	print_lines(next, STDOUT_FILENO, n_opt);
	table->error_code = NO_ERROR;
	return (table->error_code);
}
