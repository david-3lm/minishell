/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:19:43 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/14 16:07:06 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* bool	is_builtin(t_cmd *cmd)
{
	int	len;
	// t_tok *token;

	// token = (t_tok *)cmd->tokens;
	// ft_putendl_fd("HOLA", 2);
	// ft_putendl_fd(((t_tok *)cmd->tokens->content)->value, 2);
	len = (int)ft_strlen(((t_tok *)cmd->tokens->content)->value);
	//printf("HOLA \n");
	if (ft_strncmp(((t_tok *)cmd->tokens->content)->value, "echo", len) == 0 && len == 4)
		return (true);
	else if (ft_strncmp(((t_tok *)cmd->tokens->content)->value, "cd", len) == 0 && len == 2)
		return (true);
	else if (ft_strncmp(((t_tok *)cmd->tokens->content)->value, "pwd", len) == 0 && len == 3)
		return (true);
	else if (ft_strncmp(((t_tok *)cmd->tokens->content)->value, "export", len) == 0 && len == 6)
		return (true);
	else if (ft_strncmp(((t_tok *)cmd->tokens->content)->value, "unset", len) == 0 && len == 5)
		return (true);
	else if (ft_strncmp(((t_tok *)cmd->tokens->content)->value, "env", len) == 0 && len == 3)
		return (true);
	else if (ft_strncmp(((t_tok *)cmd->tokens->content)->value, "exit", len) == 0 && len == 4)
		return (true);
	return (false);
} */

int	(*builtin_arr(char *str))(t_cmd_table *table, t_cmd *cmd)
{
	static void	*builtins[7][2] = {
	{"echo", bi_echo},
	{"cd", bi_cd},
	{"pwd", bi_pwd},
	{"export", bi_export},
	{"unset", bi_unset},
	{"env", bi_env},
	{"exit", bi_exit}
	};
	// cambiar los nombres por los nombres de mis funciones
	// cómo juntar esto con el resto de la ejecucion??
	// hacer que retornen códigos de error
	int			i;

	i = 0;
	while (i < 7)
	{
		if (str)
		{
			if (!ft_strncmp(builtins[i][0], str, ft_strlen(builtins[i][0])))
				return (builtins[i][1]);
		}
		i++;
	}
	return (NULL);
}

/* int	check_built_ins(t_cmd_table *table, t_cmd *cmd)
{
	int		len;
	t_error_code	exit_status;
	t_tok *token;

	token = (t_tok *)cmd->tokens;
	exit_status = 0;
// 	if (iter_exe->n_command < mini->n_commands)
// 		close_restant_fds(iter_exe, mini, 0);
// 	else
// 		close_restant_fds(iter_exe, mini, 1);
	len = ft_strlen(token->value);
	if (ft_strncmp(token->value, "echo", len) == 0 && len == 4)
		bi_echo(table, cmd);
	else if (ft_strncmp(token->value, "cd", len) == 0 && len == 2)
		bi_cd(table, cmd);
	else if (ft_strncmp(token->value, "pwd", len) == 0 && len == 3)
		bi_pwd(table, cmd);
	else if (ft_strncmp(token->value, "export", len) == 0 && len == 6)
		bi_export(table, cmd);
	else if (ft_strncmp(token->value, "unset", len) == 0 && len == 5)
		bi_unset(table, cmd);
	else if (ft_strncmp(token->value, "env", len) == 0 && len == 3)
		bi_env(table, cmd);
	else if (ft_strncmp(token->value, "exit", len) == 0 && len == 4)
		bi_exit(table, cmd);
	return (exit_status);
} */
