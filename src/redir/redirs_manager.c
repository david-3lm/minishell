/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:52:37 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/08 19:46:20 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	manage_redir_out(t_cmd_table *table, t_redir out_redir)
{
	if (table->red_fd[READ_E] < 0 || table->red_fd[WRITE_E] < 0)
		return ;
	if (table->red_fd[WRITE_E] != 0)
		close(table->red_fd[WRITE_E]);
	if (out_redir.type == RD_SOUT)
		table->red_fd[WRITE_E] = open \
		(out_redir.direction, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (out_redir.type == RD_SOUT2)
		table->red_fd[WRITE_E] = open \
		(out_redir.direction, O_RDWR | O_CREAT | O_APPEND, 0777);
	check_error(table->red_fd[WRITE_E], CHECK_CLOSE, table);
}

void	manage_redir_in(t_cmd_table *table, t_redir in_redir)
{
	if (table->red_fd[READ_E] < 0 || table->red_fd[WRITE_E] < 0)
		return ;
	if (table->red_fd[READ_E] != 0)
		close(table->red_fd[READ_E]);
	if (in_redir.type == RD_SIN)
	{
		table->red_fd[READ_E] = open(in_redir.direction, O_RDONLY);
		check_error(table->std_backup[READ_E], CHECK_OPEN, table);
	}
	else if (in_redir.type == RD_HD)
		table->red_fd[READ_E] = manage_here_doc(in_redir, table);
}

t_redir	*get_redir_in(t_list *list)
{
	t_list	*lst_copy;
	t_redir	*redir;

	redir = NULL;
	if (ft_lstsize(list) != 0)
	{
		lst_copy = list;
		while (lst_copy != NULL)
		{
			redir = (t_redir *)lst_copy->content;
			if (redir->type == RD_SIN || redir->type == RD_HD)
			{
				printf("redirection type ==> %i \n", redir->type);
				return (redir);
			}
			lst_copy = lst_copy->next;
		}
	}
	return (NULL);
}

t_redir	*get_redir_out(t_list *list)
{
	t_list	*lst_copy;
	t_redir	*redir;

	redir = NULL;
	if (ft_lstsize(list) != 0)
	{
		lst_copy = list;
		while (lst_copy != NULL)
		{
			redir = (t_redir *)lst_copy->content;
			if (redir->type == RD_SOUT || redir->type == RD_SOUT2)
				return (redir);
			lst_copy = lst_copy->next;
		}
	}
	return (NULL);
}

void	fill_redirs(t_cmd_table *table)
{
	t_redir	*redir;
	t_list	*copy;

	copy = table->redirs;
	while (copy != NULL)
	{
		redir = (t_redir *)copy->content;
		if (redir->type == RD_SIN || redir->type == RD_HD)
			manage_redir_in(table, *redir);
		if (redir->type == RD_SOUT || redir->type == RD_SOUT2)
			manage_redir_out(table, *redir);
		copy = copy->next;
	}
	return ;
}
