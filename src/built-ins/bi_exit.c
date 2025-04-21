/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:58:31 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/21 15:47:12 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* void	bi_exit(t_cmd_table *table, t_cmd *cmd)
{
	(void)cmd;
	(void)table;
	printf("estoy haciendo exit builtin \n");
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(EXIT_SUCCESS);
	// exit libera? o tengo que liberar yo cosas?
} */

bool ft_is_strnum(char *str)
{
	int	i;

	i = 0;
	printf("\t exit value --> %s \n", str);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

int	ft_get_exit_code(t_cmd *cmd)
{
	char	*value;
	int		res;
	
	value = ((t_tok *)cmd->tokens->next->content)->value;
	// He visto que Dani hace trim a ese valor para quitarle esto "" \f\r\n\t\v"" ¿hace falta?
	if (!ft_is_strnum(value))
	{
		ft_printf("exit\n");
		ft_printf("kontxesi: exit: %s: numeric argument required\n",
			value);
		res = 2;
	}
	else
	{
		// aqui Dani hace un chequeo con los longs y tal para mirar el overflow pero creo que puedo tirar con el atoi
		// @David tu que crees? si no, lo hago tambien sin problema	
		res = (int)ft_atouc(value);
	}
	return (res);
}

void	bi_exit(t_cmd_table *table, t_cmd *cmd)
{
	int	size;
	int	exit_code;
	(void)table;
	
	exit_code = EXIT_FAILURE;
	size = ft_lstsize(cmd->tokens);
	printf("estoy haciendo exit builtin \n");
	if (size == 1)
		exit_code = EXIT_SUCCESS;
		//TODO: ¿deberia liberar cositas???
	else if (size == 2)
		exit_code = ft_get_exit_code(cmd);
	else
		ft_putstr_fd("kontxesi: exit: too many arguments\n", ERROR_E);
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(exit_code);
}
