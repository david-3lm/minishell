/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:52:37 by cde-migu          #+#    #+#             */
/*   Updated: 2025/02/27 20:34:04 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	manage_redir_in(t_cmd_table *table, t_redir in_redir)
{
	table->red_files[READ_E] = open(in_redir.direction, O_RDONLY);
	if (table->red_files[READ_E] < 0)
	{
		perror("open infile");
		exit(EXIT_FAILURE);
	}
	dup2(table->red_files[READ_E], STDIN_FILENO);
	printf("el infile se ha abierto en --> %i \n", table->red_files[READ_E]);
	printf("el outfile se ha abierto en --> %i \n", table->red_files[WRITE_E]);
}

void	manage_redir_out(t_cmd_table *table, t_redir out_redir)
{
	if (out_redir.type == RD_SOUT)
		table->red_files[WRITE_E] = open(out_redir.direction, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (out_redir.type == RD_SOUT2)
		table->red_files[WRITE_E] = open(out_redir.direction, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (table->red_files[WRITE_E] < 0)
	{
		perror("open outfile");
		exit(EXIT_FAILURE);
	}
	dup2(table->red_files[WRITE_E], STDOUT_FILENO);
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
			printf("EN IN lst copy ---> %s \n", redir->direction);
			if (redir->type == RD_SIN)
				return (redir);
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
	printf("holaaa \n");
	if (ft_lstsize(list) != 0)
	{
		lst_copy = list;
		while (lst_copy->next != NULL)
		{
			redir = (t_redir *)lst_copy;
			printf("EN OUT lst copy ---> %s \n", redir->direction);
			if (redir->type == RD_SOUT || redir->type == RD_SOUT2)
				return (redir);
			lst_copy = lst_copy->next;
		}
	}
	return (NULL);
}

void	close_red_files(int files[2])
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (files[i] != 0)
		{
			close(files[i]);
			printf("he cerrado el file %i \n \n", i);
		}
		i++;
	}
}

