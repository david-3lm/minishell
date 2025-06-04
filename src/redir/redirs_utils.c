/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:28:16 by cde-migu          #+#    #+#             */
/*   Updated: 2025/06/04 12:51:29 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ft_check_redirs(t_cmd *cmd)
{
	if ((!ft_strcmp((char *)cmd->tokens->content, "")) && (cmd->redirs != NULL))
		return (false);
	return (true);
}

bool	is_redirs(t_list *redirs, t_redir_type type)
{
	int		check;
	t_redir	*redir;

	check = false;
	while (redirs)
	{
		redir = (t_redir *)redirs->content;
		if (redir->type == type)
		{
			check = true;
			break ;
		}
		redirs = redirs->next;
	}
	return (check);
}

int	open_file(t_redir *redir, int prev_fd, int flags, mode_t permissions)
{
	char	*file_name;
	int		new_fd;

	if (prev_fd != -2)
		close(prev_fd);
	file_name = redir->direction;
	new_fd = open(file_name, flags, permissions);
	if (new_fd == -1)
		error_handler(OPEN_ERROR);
	else
	{
		if (redir->type == RD_SIN)
			dup2(new_fd, STDIN_FILENO);
		else if (redir->type == RD_SOUT || redir->type == RD_SOUT2)
			dup2(new_fd, STDOUT_FILENO);
		close(new_fd);
	}
	return (new_fd);
}

int	open_all_files(t_list *redirs, t_cmd_table *table)
{
	int		read_fd;
	int		w_fd;
	t_redir	*redir;

	read_fd = -2;
	w_fd = -2;
	while (redirs)
	{
		redir = (t_redir *)redirs->content;
		if (redir->type == RD_SOUT)
			w_fd = open_file(redir, w_fd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (redir->type == RD_SOUT2)
			w_fd = open_file(redir, w_fd, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (redir->type == RD_SIN)
			read_fd = open_file(redir, read_fd, O_RDONLY, 0);
		else if (redir->type == RD_HD)
			read_fd = manage_here_doc(redir, table);
		if (read_fd == -1 || w_fd == -1)
		{
			table->error_code = UNKNOWN_ERROR;
			return (table->error_code);
		}
		redirs = redirs->next;
	}
	return (table->error_code);
}

void	close_red_fd(int files[2])
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (files[i] != 0)
			close(files[i]);
		i++;
	}
}