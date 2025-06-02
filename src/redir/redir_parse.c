/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:53:31 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/06/01 18:59:44 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_redir(t_cmd *cmd, t_list *new_n, const char *input, int *curr_pos)
{
	if (ft_lstsize(cmd->tokens) == 0)
	{
		new_n = ft_lstnew((void *)get_token(input, curr_pos));
		if (!new_n)
			error_handler(EXIT_FAILURE);
		ft_lstadd_back(&cmd->tokens, new_n);
	}
	new_n = ft_lstnew((void *)get_redir(input, curr_pos));
	if (!new_n)
		error_handler(EXIT_FAILURE);
	ft_lstadd_back(&cmd->redirs, new_n);
}

void	set_redir_type(t_redir *redir, const char *input, int curr_pos)
{
	if (!ft_strncmp(&input[curr_pos], "<<", 2))
		redir->type = RD_HD;
	else if (input[curr_pos] == '<')
		redir->type = RD_SIN;
	else if (!ft_strncmp(&input[curr_pos], ">>", 2))
		redir->type = RD_SOUT2;
	else if (input[curr_pos] == '>')
		redir->type = RD_SOUT;
}
