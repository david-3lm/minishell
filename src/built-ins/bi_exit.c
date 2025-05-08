/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:58:31 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/08 11:19:40 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ft_is_strnum(char *str)
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
	if (!ft_is_strnum(value))
	{
		ft_printf("exit\n");
		ft_printf("kontxesi: exit: %s: numeric argument required\n",
			value);
		res = 2;
	}
	else
		res = (int)ft_atouc(value);
	return (res);
}

int	bi_exit(t_cmd_table *table, t_cmd *cmd)
{
	int	size;

	(table)->error_code = EXIT_FAILURE;
	size = ft_lstsize(cmd->tokens);
	if (size == 1)
		(table)->error_code = EXIT_SUCCESS;
	else if (size == 2)
		(table)->error_code = ft_get_exit_code(cmd);
	else
	{
		ft_putstr_fd("kontxesi: exit: too many arguments\n", ERROR_E);
		(table)->error_code = UNKNOWN_ERROR;
		return ((table)->error_code);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit((table)->error_code);
	return ((table)->error_code);
}
