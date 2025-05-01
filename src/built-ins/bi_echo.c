/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:03:41 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/01 11:52:49 by dlopez-l         ###   ########.fr       */
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

bool	is_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

t_list	*check_n_flag(t_list *next, bool *n_opt)
{
	char	*aux;

	if (!next || !next->content)
		return (next);
	aux = (char *)((t_tok *)next->content)->value;
	if (is_n_option(aux))
	{
		*n_opt = true;
		return (next->next);
	}
	return (next);
}

int	bi_echo(t_cmd_table *table, t_cmd *cmd)
{
	t_list	*next;
	bool	n_opt;

	(void)table;
	n_opt = false;
	next = cmd->tokens->next;
	if (!next)
		ft_putendl_fd("", STDOUT_FILENO);
	else
	{
		next = check_n_flag(next, &n_opt);
		print_lines(next, STDOUT_FILENO, n_opt);
	}
	table->error_code = NO_ERROR;
	return (table->error_code);
}
